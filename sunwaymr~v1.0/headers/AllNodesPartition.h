/*
 * AllNodesPartition.h
 *
 *	Partition of AllNodesDCUS
 *
 *  Created on: Jan 17, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_ALLNODESPARTITION_H_
#define HEADERS_ALLNODESPARTITION_H_

#include <vector>

#include "IteratorSeq.h"
#include "Partition.h"
using std::vector;

class AllNodesPartition : public Partition {
public:
	AllNodesPartition(long DCUSID, int partitionID, IteratorSeq<void *> &values);
	IteratorSeq<void *> iteratorSeq();

	long DCUSID;
	int partitionID;
	IteratorSeq<void *> &values;
};



#endif /* HEADERS_ALLNODESPARTITION_H_ */
