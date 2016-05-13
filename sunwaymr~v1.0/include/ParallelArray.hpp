#ifndef PARALLELARRAY_HPP_
#define PARALLELARRAY_HPP_


#include "ParallelArray.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "IteratorSeq.hpp"
#include "DCUS.hpp"
#include "Partition.hpp"
#include "SunwayMRContext.hpp"
#include "ParallelArrayPartition.hpp"
using namespace std;

//template <class T> long ParallelArray<T>::current_id = 1; // moved to DCUS

template <class T>
ParallelArray<T>::ParallelArray(SunwayMRContext &c, IteratorSeq<T> &seq, int numSlices)
	: DCUS<T>::DCUS (c) , seq(seq), numSlices(numSlices)
{
//	this->logInfo("ParallelArray: creating partitions...");
	parallelArray_id = DCUS<T>::DCUSID;
	//parallelArray_id = DCUS<T>::current_id++;
	// get partitions
	vector<Partition*> partitions;

	vector< IteratorSeq<T>* > slices = slice();

	if(slices.size() == 0) {
		exit(104);
	}

	//construct partitions
	for (unsigned int i = 0; i < slices.size(); i++)
	{
		Partition* partition = new ParallelArrayPartition<T>(parallelArray_id, i, *slices[i]);
		partitions.push_back(partition);
	}

	DCUS<T>::partitions = partitions;

//	stringstream partitionsInfo;
//	partitionsInfo << "ParallelArray: " << DCUS<T>::partitions.size() << " partitions created";
//	this->logInfo(partitionsInfo.str());
}

template <class T>
vector<Partition*> ParallelArray<T>::getPartitions()
{
	return DCUS<T>::partitions;
}

template <class T>
vector<string> ParallelArray<T>::preferredLocations(Partition &p)
{
	vector<string> list;
	return list;
}

template <class T>
IteratorSeq<T> ParallelArray<T>::iteratorSeq(Partition &p)
{
	ParallelArrayPartition<T> &pap = dynamic_cast<ParallelArrayPartition<T>&>(p);
	return pap.iteratorSeq();
}

template <class T>
vector< IteratorSeq<T>* > ParallelArray<T>::slice()
{
	vector< IteratorSeq<T>* > slices;
	if (numSlices < 1)
	{
//		logError("ParallelArray: slice number should be positive integer!");
		return slices;
	}

	long seqSize = seq.size();
	long num_group = seqSize / numSlices;

	if (seq.type == 0)
	{
		T step = seq.at(1) - seq.at(0);
		for (int i = 0; i < numSlices - 1; i++)
		{
			T start = seq.at(0) + i * num_group * step;
			T end = start + (num_group - 1) * step;
			IteratorSeq<T> *it = new IteratorSeq<T>(start, end , step);
			slices.push_back(it);
		}
		T last_start = seq.at(0) + (numSlices - 1) * num_group * step;
		T end = seq.at(seqSize-1);
		IteratorSeq<T> *last = new IteratorSeq<T>(last_start, end, step);
		slices.push_back(last);
	}
	else
	{
		// type == 1
		for (int i = 0; i < numSlices - 1; i++)
		{
			vector<T> group;
			for (long j = 0; j < num_group; j++)
			{
				group.push_back(seq.at(i * num_group + j));
			}
			IteratorSeq<T> *it = new IteratorSeq<T>(group);
			slices.push_back(it);
		}
		vector<T> last;
		for (long i = (numSlices - 1) * num_group; i < seq.size(); i++)
		{
			last.push_back(seq.at(i));
		}
		IteratorSeq<T> *it = new IteratorSeq<T>(last);
		slices.push_back(it);
	}

	return slices;
}


#endif /* PARALLELARRAY_HPP_ */
