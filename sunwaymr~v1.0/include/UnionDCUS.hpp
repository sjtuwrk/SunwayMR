/*
 * UnionDCUS.hpp
 *
 *  Created on: Feb 26, 2016
 *      Author: yupeng
 */

#ifndef INCLUDE_UNIONDCUS_HPP_
#define INCLUDE_UNIONDCUS_HPP_

#include "UnionDCUS.h"

#include <iostream>
#include "IteratorSeq.hpp"
#include "Partition.hpp"
#include "DCUS.hpp"
#include "SunwayMRContext.hpp"
#include "UnionPartition.hpp"
using namespace std;

template <class T>
UnionDCUS<T>::UnionDCUS(SunwayMRContext &context, vector< DCUS<T>* > DCUSs)
:DCUS<T>::DCUS(context), DCUSs(DCUSs) {
	long unionDCUS_id = DCUS<T>::DCUSID;
	vector<Partition*> partitions;
	int partition_id = 0;
	for (unsigned int i=0; i<DCUSs.size(); i++) {
		vector<Partition*> vp = DCUSs[i]->getPartitions();
		for (unsigned int j=0; j<vp.size(); j++) {
			Partition *p = new UnionPartition<T>(unionDCUS_id, partition_id, DCUSs[i], vp[j]);
			partitions.push_back(p);
			partition_id ++;
		}
	}
	DCUS<T>::partitions = partitions;
}

template <class T>
vector<Partition*> UnionDCUS<T>::getPartitions() {
	return DCUS<T>::partitions;
}

template <class T>
vector<string> UnionDCUS<T>::preferredLocations(Partition &p) {
	UnionPartition<T> &up = dynamic_cast<UnionPartition<T>&>(p);
	return up.preferredLocations();
}

template <class T>
IteratorSeq<T> UnionDCUS<T>::iteratorSeq(Partition &p) {
	UnionPartition<T> &up = dynamic_cast<UnionPartition<T>&>(p);
	return up.iteratorSeq();
}

template <class T>
void UnionDCUS<T>::shuffle() {
	for(unsigned int i=0; i<DCUSs.size(); i++) {
		DCUSs[i]->shuffle();
	}
}

#endif /* INCLUDE_UNIONDCUS_HPP_ */
