/*
 * TextFileDCUS.h
 *
 * Context::textFile() creates TextFileDCUS.
 * TextFileDCUS is constructed from vector<FileSource>.
 * TextFileDCUS creates TextFileBlocks from files, and partition them into TextFilePartitions
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_TEXTFILEDCUS_H_
#define HEADERS_TEXTFILEDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "DCUS.h"
#include "SunwayMRContext.h"
#include "TextFilePartition.h"
#include "TextFileBlock.h"
#include "FileSource.h"
using std::vector;
using std::string;

template <class T> class DCUS;
class SunwayMRContext;

class TextFileDCUS : public DCUS<TextFileBlock> {
public:
	TextFileDCUS(SunwayMRContext &c, vector<FileSource> files, int numSlices, FileSourceFormat format = FILE_SOURCE_FORMAT_BYTE);
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<TextFileBlock> iteratorSeq(Partition &p);
	vector< IteratorSeq<TextFileBlock>* > slice();

	//data
	//IteratorSeq<TextFileBlock> &seq;
	vector<FileSource> files;
	int numSlices;
	FileSourceFormat format;
	long textFileDCUS_id;

};


#endif /* HEADERS_TEXTFILEDCUS_H_ */
