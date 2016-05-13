/*
 * ParallelArrayPartition.h
 *
 * DCUS partition of ParallelArray (ParallelArray is a DCUS type).
 * With a part of IteratorSeq values of ParallelArray.
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef PARALLELARRAYPARTITION_H_
#define PARALLELARRAYPARTITION_H_

#include <vector>

#include "IteratorSeq.h"
#include "Partition.h"
using std::vector;

template <class T>
class ParallelArrayPartition: public Partition {
public:
	ParallelArrayPartition(long DCUSID, int partitionID, IteratorSeq<T> &values);
	IteratorSeq<T> iteratorSeq();

	long DCUSID;
	int partitionID;
	IteratorSeq<T> &values;
};


#endif /* PARALLELARRAYPARTITION_H_ */
