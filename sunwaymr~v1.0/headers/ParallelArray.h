/*
 * ParallelArray.h
 *
 * A DCUS type with IteratorSeq values, e.g. 1...1000
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef PARALLELARRAY_H_
#define PARALLELARRAY_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "ParallelArrayPartition.h"
#include "DCUS.h"
#include "SunwayMRContext.h"
using std::vector;
using std::string;

template <class T> class DCUS;
template <class U, class T> class MappedDCUS;
class SunwayMRContext;

template <class T>
class ParallelArray : public DCUS<T> {
public:
	ParallelArray(SunwayMRContext &c, IteratorSeq<T> &seq, int numSlices);
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<T> iteratorSeq(Partition &p);
	vector< IteratorSeq<T>* > slice();

	//data
	IteratorSeq<T> &seq;
	int numSlices;
	long parallelArray_id;

//	static long current_id; // moved to DCUS
};


#endif /* PARALLELARRAY_H_ */
