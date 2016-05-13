/*
 * AllNodesDCUS.h
 *
 * A DCUS with a same partition on each node.
 * An easy way to run the same code on all nodes.
 *
 *  Created on: Jan 17, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_ALLNODESDCUS_H_
#define HEADERS_ALLNODESDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "AllNodesPartition.h"
#include "DCUS.h"
#include "SunwayMRContext.h"
using std::vector;
using std::string;

template <class T> class DCUS;
template <class U, class T> class MappedDCUS;
class SunwayMRContext;

class AllNodesDCUS : public DCUS<void *> {
public:
	AllNodesDCUS(SunwayMRContext &c, IteratorSeq<void *> &seq);
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<void *> iteratorSeq(Partition &p);

	//data
	IteratorSeq<void *> &seq;
	long DCUS_id;
};


#endif /* HEADERS_ALLNODESDCUS_H_ */
