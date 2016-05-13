/*
 * PairDCUS.h
 *
 * Return type of DCUS::mapToPair.
 * PairDCUS values are all Pairs.
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_PAIRDCUS_H_
#define HEADERS_PAIRDCUS_H_

#include <vector>
#include <string>

#include "IteratorSeq.h"
#include "Partition.h"
#include "DCUS.h"
#include "Pair.h"
#include "MappedDCUS.h"
#include "Either.h"

using std::vector;
using std::string;

template <class T> class DCUS;
template <class K, class V, class T>
class PairDCUS : public DCUS< Pair<K, V> > {
public:
	PairDCUS(DCUS<T> &prev, Pair<K, V> (*f)(T));
	//PairDCUS<K, V, T> & operator=(const PairDCUS<K, V, T> &p);
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq< Pair<K, V> > iteratorSeq(Partition &p);
	void shuffle();

	template <class U>
	PairDCUS<K, U, Pair<K, V> > & mapValues(Pair<K, U> (*f)(Pair<K, V>)); // change value's type

	MappedDCUS<V, Pair< K, V > > & values(); // get all values

	template <class C>
	PairDCUS<K, C, Pair<K, C> > & combineByKey(Pair<K, C> (*createCombiner)(Pair<K, V>),
			Pair<K, C> (*mergeCombiner)(Pair<K, C>, Pair<K, C>),
			int numPartitions); // used by redueceByKey and groupByKey

	PairDCUS<K, V, Pair<K, V> > & reduceByKey(
			Pair<K, V> (*reduce_function)(Pair<K, V>, Pair<K, V>),
			int numPartitions); // shuffle operator

	PairDCUS<K, V, Pair<K, V> > & reduceByKey(Pair<K, V> (*reduce_function)(Pair<K, V>, Pair<K, V>)); // shuffle operator

	PairDCUS<K, IteratorSeq<V>, Pair<K, IteratorSeq<V> > > & groupByKey(int num_partitions); // shuffle operator

	PairDCUS<K, IteratorSeq<V>, Pair<K, IteratorSeq<V> > > & groupByKey(); // shuffle operator

	template <class W>
	PairDCUS< K, Pair< V, W >, Pair< K, Pair< V, W > > > & join(
			DCUS< Pair< K, W > > &other,
			int num_partitions); // join two PairDCUS

	template <class W>
	PairDCUS< K, Pair< V, W >, Pair< K, Pair< V, W > > > & join(
			DCUS< Pair< K, W > > &other); // join two PairDCUS

private:
	DCUS<T> &prevDCUS;
	Pair<K, V> (*mapToPairFunction)(T);
};



#endif /* HEADERS_PAIRDCUS_H_ */
