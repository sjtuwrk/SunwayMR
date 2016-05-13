/*
 * TextFileDCUS.hpp
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef TEXTFILEDCUS_HPP_
#define TEXTFILEDCUS_HPP_

#include "TextFileDCUS.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <limits.h>

#include "IteratorSeq.hpp"
#include "DCUS.hpp"
#include "Partition.hpp"
#include "SunwayMRContext.hpp"
#include "TextFilePartition.hpp"
#include "TextFileBlock.hpp"
#include "FileSource.hpp"
#include "AllNodesDCUS.hpp"
#include "Utils.hpp"
using namespace std;

TextFileDCUS::TextFileDCUS(SunwayMRContext &c, vector<FileSource> files, int numSlices, FileSourceFormat format)
: DCUS<TextFileBlock>::DCUS (c), files(files), numSlices(numSlices), format(format) {
	//textFileDCUS_id = DCUS<TextFileBlock>::current_id++;
	textFileDCUS_id = DCUS<TextFileBlock>::DCUSID;
	// calculate partitions
	vector<Partition*> partitions;
	vector< IteratorSeq<TextFileBlock>* > slices = slice();

	if(slices.size() < 1) {
		exit(104);
	}

	//construct partitions
	for (unsigned int i = 0; i < slices.size(); i++)
	{
		Partition* partition = new TextFilePartition(textFileDCUS_id, i, *slices[i]);
		partitions.push_back(partition);
	}

	DCUS<TextFileBlock>::partitions = partitions;
}


vector<Partition*> TextFileDCUS::getPartitions() {
	return DCUS<TextFileBlock>::partitions;
}

vector<string> TextFileDCUS::preferredLocations(Partition &p) {
	TextFilePartition &partition = dynamic_cast<TextFilePartition&>(p);
	return partition.blockLocations;
}

IteratorSeq<TextFileBlock> TextFileDCUS::iteratorSeq(Partition &p) {
	TextFilePartition &pap = dynamic_cast<TextFilePartition&>(p);
	return pap.iteratorSeq();
}

string master_ip;
int scheduler_listen_port;
FileSource getFileSize(void *file) {
	FileSource* fs = (FileSource*)file;
	string selfIP = getLocalHost();

	if(fs->source=="*" || fs->source==selfIP) {
		fs->location = selfIP;
		fs->listenPort = scheduler_listen_port;

		long bytes, lines;
		getFileLength(fs->path, bytes);
		getFileLineNumber(fs->path, lines);
		fs->bytes = bytes;
		fs->lines = lines;
		if (fs->format == FILE_SOURCE_FORMAT_BYTE) {
			fs->length = bytes;
		} else {
			fs->length = lines;
		}
	} else if (fs->source=="[DFS-server]" && selfIP==master_ip) {
		// TODO DFS file

	}

	FileSource fs_ret(*fs);
	return fs_ret;
}


vector< IteratorSeq<TextFileBlock>* > TextFileDCUS::slice() {
	vector<void *> seq;
	for(unsigned int i=0; i<files.size(); i++) {
		files[i].format = this->format;
		seq.push_back(&files[i]);
	}
	master_ip = DCUS<TextFileBlock>::context.getMaster();
	scheduler_listen_port = DCUS<TextFileBlock>::context.getListenPort();
	// collect all file sizes
	IteratorSeq<void *> *is = new IteratorSeq<void *>(seq);
	vector<FileSource> fileSources = DCUS<TextFileBlock>::context.allNodes(*is).map(getFileSize).collect();

	long total_length = 0, total_bytes = 0, total_lines = 0;
	for(unsigned int i=0; i<fileSources.size(); i++) {
		total_length += fileSources[i].length;
		total_bytes += fileSources[i].bytes;
		total_lines += fileSources[i].lines;
	}

	// create file blocks, slice
	vector< IteratorSeq<TextFileBlock>* > ret;
	if(total_length > 0) {
		// calculate block length
		int max_block_size = MAX_TEXT_FILE_BLOCK_SIZE_BYTE;
		if (this->format == FILE_SOURCE_FORMAT_LINE) max_block_size = MAX_TEXT_FILE_BLOCK_SIZE_BYTE / (total_bytes / total_lines);
		long b = total_length / numSlices;
		b += 1;
		if (b > max_block_size) b = max_block_size;
		//if (b == 0) b = 1;
		//else if (b > MAX_TEXT_FILE_BLOCK_SIZE) b = MAX_TEXT_FILE_BLOCK_SIZE;

		int allBlocksCount = 0;

		// get all blocks
		vector< vector<TextFileBlock> > allBlocks;
		for(unsigned int i=0; i<fileSources.size(); i++) {
			FileSource fs = fileSources[i];
			vector<TextFileBlock> fileBlocks;
			long l1 = 0;
			if (fs.length > 0) {
				int fileBlocksCount = fs.length / b;
				if(fs.length % b > 0) fileBlocksCount++;

				while(true) {
					if(l1+b <= fs.length) {
						TextFileBlock block = TextFileBlock(fs, fs.location, l1, b, fs.format);
						fileBlocks.push_back(block);
						l1 += b;
					} else {
						TextFileBlock block = TextFileBlock(fs, fs.location, l1, fs.length-l1, fs.format);
						fileBlocks.push_back(block);
						break;
					}
				}
				allBlocks.push_back(fileBlocks);
				allBlocksCount += fileBlocks.size();
			}
		}

		// slice blocks
		unsigned int partitionBlocksCount = allBlocksCount / numSlices;
		unsigned int partitionBlocksCountMax = partitionBlocksCount;
		if (partitionBlocksCount == 0) {
			partitionBlocksCount = 1;
			partitionBlocksCountMax = 1;
		}
		else if (allBlocksCount % numSlices > 0) partitionBlocksCountMax++;

		// 1. remove extra
		if(allBlocks.size() > (unsigned)numSlices) {
			for (unsigned int i=numSlices; i<allBlocks.size(); i++) {
				unsigned int smallest = INT_MAX, smallestIndex = 0;
				for (int j=0; j<numSlices; j++) {
					if (allBlocks[j].size() < smallest) {
						smallest = allBlocks[j].size();
						smallestIndex = j;
					}
				}

				allBlocks[i].insert(allBlocks[i].end(),
						allBlocks[smallestIndex].begin(),
						allBlocks[smallestIndex].end());
			}
			allBlocks.erase(allBlocks.begin()+numSlices, allBlocks.end());
		}

		// 2. add to numSlices
		if(allBlocks.size() < (unsigned)numSlices) {
			unsigned int num = numSlices-allBlocks.size();
			for (unsigned int i=0; i<num; i++) {
				vector<TextFileBlock> emptyFileBlocks;
				allBlocks.push_back(emptyFileBlocks);
			}
		}

		// 3. balancing
		while (true) {
			unsigned int smallest = INT_MAX, smallestIndex = 0, biggest = 0, biggestIndex = 0;
			for (int j=0; j<numSlices; j++) {
				if (allBlocks[j].size() < smallest) {
					smallest = allBlocks[j].size();
					smallestIndex = j;
				}

				if (allBlocks[j].size() > biggest) {
					biggest = allBlocks[j].size();
					biggestIndex = j;
				}
			}

			if (biggest <= partitionBlocksCountMax
					|| smallestIndex==biggestIndex
					|| biggest - smallest <= 1) {
				if (smallest == 0 && biggest >=2) {
					allBlocks[smallestIndex].insert(allBlocks[smallestIndex].end(),
							allBlocks[biggestIndex].end()-1,
							allBlocks[biggestIndex].end());
					allBlocks[biggestIndex].erase(allBlocks[biggestIndex].end()-1,
							allBlocks[biggestIndex].end());
				} else {
					break;
				}
			} else {
				// move blocks
				int a = biggest - partitionBlocksCountMax;
				int b = partitionBlocksCountMax -smallest;
				int c = a < b ? a : b;
				allBlocks[smallestIndex].insert(allBlocks[smallestIndex].end(),
						allBlocks[biggestIndex].end()-c,
						allBlocks[biggestIndex].end());
				allBlocks[biggestIndex].erase(allBlocks[biggestIndex].end()-c,
						allBlocks[biggestIndex].end());

			}
		}

		// done
		for (unsigned int i=0; i<allBlocks.size(); i++) {
			IteratorSeq<TextFileBlock> *it = new IteratorSeq<TextFileBlock>(allBlocks[i]);
			ret.push_back(it);
		}

	} else {
		Logging::logWarning("TextFileDCUS: total file length is 0.");
	}

	return ret;
}


#endif /* TEXTFILEDCUS_HPP_ */

