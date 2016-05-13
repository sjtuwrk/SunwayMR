/*
 * UnionPartition.h
 *
 * Partition of UnionDCUS.
 * Constructed from a pointer *DCUS and a pointer *partition.
 * The DCUS and partition above is from UnionDCUS.
 *
 *  Created on: Feb 26, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_UNIONPARTITION_H_
#define HEADERS_UNIONPARTITION_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "Partition.h"
using std::vector;
using std::string;

template <class T>
class UnionPartition: public Partition {
public:
	UnionPartition(long DCUSID, int partitionID, DCUS<T> *DCUS, Partition *partition);
	IteratorSeq<T> iteratorSeq();
	vector<string> preferredLocations();

	long DCUSID;
	int partitionID;
	DCUS<T> *DCUS;
	Partition *partition;
};



#endif /* HEADERS_UNIONPARTITION_H_ */
