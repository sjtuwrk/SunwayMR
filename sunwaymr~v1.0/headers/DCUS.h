/*
 * DCUS.h
 *
 * Abstract super class of all other DCUS classes.
 * With some general interfaces of DCUS.
 * So, every DCUS has operator: map, flatmap, mapToPair,
 * 		reduce , shuffle, distinct, collect, unionDCUS
 *
 * Some operator will return a new DCUS.
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef DCUS_H_
#define DCUS_H_

#include <string>
#include <vector>

#include "IteratorSeq.h"
#include "MappedDCUS.h"
#include "FlatMappedDCUS.h"
#include "PairDCUS.h"
#include "Partition.h"
#include "SunwayMRContext.h"
#include "UnionDCUS.h"
using std::string;
using std::vector;


template <class U, class T> class MappedDCUS;
template <class U, class T> class FlatMappedDCUS;
template <class K, class V, class T> class PairDCUS;
class SunwayMRContext;

long XYZ_CURRENT_DCUS_ID = 1; // id counter

template <class T>
class DCUS {
public:
	DCUS(SunwayMRContext &c);
	DCUS<T> & operator=(const DCUS<T> &p);
	virtual ~DCUS();
	virtual void initDCUSFrom(const DCUS<T> &r);
	virtual vector<Partition*> getPartitions()=0;
	virtual vector<string> preferredLocations(Partition &p)=0;
	virtual IteratorSeq<T> iteratorSeq(Partition &p)=0;

	template <class U> MappedDCUS<U, T> & map(U (*f)(T));
	template <class U> FlatMappedDCUS<U, T> & flatMap(vector<U> (*f)(T));
	template <class K, class V> PairDCUS<K, V, T> & mapToPair(Pair<K, V> (*f)(T));
	T reduce(T (*g)(T, T));
	virtual void shuffle();

	MappedDCUS<T, Pair< T, int > > & distinct(int newNumSlices);
	MappedDCUS<T, Pair< T, int > > & distinct(); // by default, newNumSlices = partitions.size()
	vector<T>& collect();

	UnionDCUS<T> & unionDCUS(DCUS<T> *other);

	SunwayMRContext &context;
	vector<Partition*> partitions;
	long DCUSID;
};


#endif /* DCUS_H_ */
