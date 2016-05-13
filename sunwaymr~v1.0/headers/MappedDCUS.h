/*
 * MappedDCUS.h
 *
 * Return type of DCUS::map.
 * Mapping mappedFunction to each value of DCUS.
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef MAPPEDDCUS_H_
#define MAPPEDDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "Partition.h"
#include "DCUS.h"
using std::vector;
using std::string;

template <class T> class DCUS;

template <class U, class T>
class MappedDCUS : public DCUS<U> {
public:
	MappedDCUS(DCUS<T> &prev, U (*f)(T));
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq<U> iteratorSeq(Partition &p);
	void shuffle();

private:
	DCUS<T> &prevDCUS;
	U (*mappedFunction)(T);
};



#endif /* MAPPEDDCUS_H_ */
