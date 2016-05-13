/*
 * UnionDCUSPartition.hpp
 *
 *  Created on: Feb 26, 2016
 *      Author: yupeng
 */

#ifndef INCLUDE_UNIONPARTITION_HPP_
#define INCLUDE_UNIONPARTITION_HPP_

#include "UnionPartition.h"

#include <iostream>

#include "IteratorSeq.hpp"
#include "Partition.hpp"
using namespace std;

template <class T>
UnionPartition<T>::UnionPartition(long DCUSID, int partitionID, DCUS<T> *DCUS, Partition *partition)
:DCUSID(DCUSID), partitionID(partitionID), DCUS(DCUS), partition(partition) {

}

template <class T>
IteratorSeq<T> UnionPartition<T>::iteratorSeq() {
	return DCUS->iteratorSeq(*partition);
}

template <class T>
vector<string> UnionPartition<T>::preferredLocations() {
	return DCUS->preferredLocations(*partition);
}

#endif /* INCLUDE_UNIONPARTITION_HPP_ */
