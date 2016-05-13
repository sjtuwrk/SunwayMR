/*
 * FlatMappedDCUS.h
 *
 * DCUS::flatmap will return a FlatMappedDCUS
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_FLATMAPPEDDCUS_H_
#define HEADERS_FLATMAPPEDDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "Partition.h"
#include "DCUS.h"
using std::vector;
using std::string;

template <class T> class DCUS;

template <class U, class T>
class FlatMappedDCUS : public DCUS<U> {
public:
	FlatMappedDCUS(DCUS<T> &prev, vector<U> (*f)(T));
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<U> iteratorSeq(Partition &p);
	void shuffle();

private:
	DCUS<T> &prevDCUS;
	vector<U> (*mappedFunction)(T);
};


#endif /* HEADERS_FLATMAPPEDDCUS_H_ */
