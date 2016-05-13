/*
 * UnionDCUS.h
 *
 * Return type of DCUS::unionDCUS.
 * To union numbers of DCUSs.
 * Create UnionDCUSPartitions for each DCUS and each partition in DCUSs.
 *
 *  Created on: Feb 26, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_UNIONDCUS_H_
#define HEADERS_UNIONDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "Partition.h"
#include "SunwayMRContext.h"
#include "DCUS.h"
using std::vector;
using std::string;

template <class T> class DCUS;
class SunwayMRContext;

template <class T>
class UnionDCUS : public DCUS<T> {
public:
	UnionDCUS(SunwayMRContext &context, vector< DCUS<T>* > DCUSs);
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<T> iteratorSeq(Partition &p);
	void shuffle();

private:
	vector< DCUS<T>* > DCUSs;
};



#endif /* HEADERS_UNIONDCUS_H_ */
