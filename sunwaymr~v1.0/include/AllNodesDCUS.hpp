/*
 * AllNodesDCUS.hpp
 *
 *  Created on: Jan 17, 2016
 *      Author: yupeng
 */

#ifndef ALLNODESDCUS_HPP_
#define ALLNODESDCUS_HPP_

#include "AllNodesDCUS.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "IteratorSeq.hpp"
#include "DCUS.hpp"
#include "Partition.hpp"
#include "SunwayMRContext.hpp"
#include "AllNodesPartition.hpp"
using namespace std;

AllNodesDCUS::AllNodesDCUS(SunwayMRContext &c, IteratorSeq<void *> &seq)
: DCUS<void *>::DCUS (c) , seq(seq){
	//DCUS_id = DCUS<void *>::current_id++;
	DCUS_id = DCUS<void *>::DCUSID;

	vector<Partition*> partitions;
	vector<string> hosts = c.getHosts();
	for (unsigned int i=0; i<hosts.size(); i++) {
		Partition* partition = new AllNodesPartition(DCUS_id, i, seq);
		partitions.push_back(partition);
	}

	DCUS<void *>::partitions = partitions;
}

vector<Partition*> AllNodesDCUS::getPartitions() {
	return DCUS<void *>::partitions;
}

vector<string> AllNodesDCUS::preferredLocations(Partition &p) {
	vector<string> ret;

	vector<string> hosts = DCUS<void *>::context.getHosts();
	AllNodesPartition &partition = dynamic_cast<AllNodesPartition&>(p);
	ret.push_back(hosts[partition.partitionID]);

	return ret;
}

IteratorSeq<void *> AllNodesDCUS::iteratorSeq(Partition &p) {
	AllNodesPartition &partition = dynamic_cast<AllNodesPartition&>(p);
	return partition.iteratorSeq();
}

#endif /* ALLNODESDCUS_HPP_ */

