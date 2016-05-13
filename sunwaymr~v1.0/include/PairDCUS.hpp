/*
 * PairDCUS.hpp
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef PAIRDCUS_HPP_
#define PAIRDCUS_HPP_

#include "PairDCUS.h"

#include <iostream>
#include <vector>
#include "IteratorSeq.hpp"
#include "Partition.hpp"
#include "DCUS.hpp"
#include "Pair.hpp"
#include "ShuffledDCUS.hpp"
#include "Aggregator.hpp"
#include "HashDivider.hpp"
#include "Either.hpp"
#include "MappedDCUS.hpp"
#include "UnionDCUS.hpp"

using namespace std;

template <class K, class V, class T>
PairDCUS<K, V, T>::PairDCUS(DCUS<T> &prev, Pair<K, V> (*f)(T))
:DCUS< Pair<K, V> >::DCUS(prev.context), prevDCUS(prev)
{
	mapToPairFunction = f;
}

//template <class K, class V, class T>
//PairDCUS<K, V, T> & PairDCUS<K, V, T>::operator=(const PairDCUS<K, V, T> &p) {
//	this->initDCUSFrom(p);
//	this->prevDCUS = p.prevDCUS;
//	this->mapToPairFunction = p.mapToPairFunction;
//	return *this;
//}

template <class K, class V, class T>
void PairDCUS<K, V, T>::shuffle()
{
	prevDCUS.shuffle();
}

template <class K, class V, class T>
vector<Partition*> PairDCUS<K, V, T>::getPartitions()
{
	return prevDCUS.getPartitions();
}

template <class K, class V, class T>
vector<string> PairDCUS<K, V, T>::preferredLocations(Partition &p)
{
	return prevDCUS.preferredLocations(p);
}

template <class K, class V, class T>
IteratorSeq< Pair<K, V> >  PairDCUS<K, V, T>::iteratorSeq(Partition &p)
{
	IteratorSeq<T> seq1 = prevDCUS.iteratorSeq(p);
	return seq1.map(mapToPairFunction);
}

template <class K, class V, class T>
template <class U>
PairDCUS<K, U, Pair<K, V> > & PairDCUS<K, V, T>::mapValues(Pair<K, U> (*f)(Pair<K, V>))
{
	PairDCUS<K, U, Pair<K, V> > *pair_DCUS = new PairDCUS<K, U, Pair<K, V> >(*this, f);
	return *pair_DCUS;
}

template <class K, class V>
Pair< K, V > xyz_pair_DCUS_do_nothing_f(Pair< K, V > p) {
	return p;
}


template <class K, class V>
V xyz_pair_DCUS_values_inner_map_f (Pair< K, V > p) {
	return p.v2;
}

template <class K, class V, class T>
MappedDCUS<V, Pair< K, V > > & PairDCUS<K, V, T>::values() {
	return this->map(xyz_pair_DCUS_values_inner_map_f< K, V >);
}

template <class K, class C>
long xyz_pair_DCUS_combineByKey_inner_hash_f (Pair<K, C> &p, stringstream &ss) {
	ss << p.v1;
	long ret = hash(ss.str());
	ss.str(string());
	ss.clear();
	return ret;
}

template <class K, class C>
string xyz_pair_DCUS_combineByKey_inner_to_string_f (Pair<K, C> &p, stringstream &ss) {
	ss << p;
	string ret = ss.str();
	ss.str(string());
	ss.clear();
	return ret;
}

template <class K, class C>
Pair<K, C> xyz_pair_DCUS_combineByKey_inner_from_string_f (string &s, stringstream &ss) {
	Pair<K, C> p;
	p.fromString(s, ss);
	ss.str(string());
	ss.clear();
	return p;
}

template <class K, class V, class T>
template <class C>
PairDCUS<K, C, Pair<K, C> > & PairDCUS<K, V, T>::combineByKey(
		Pair<K, C> (*createCombiner)(Pair<K, V>),
		Pair<K, C> (*mergeCombiner)(Pair<K, C>, Pair<K, C>),
		int numPartitions)
 {
	Aggregator< Pair<K, V>, Pair<K, C> > *agg = new Aggregator< Pair<K, V>, Pair<K, C> >(createCombiner, mergeCombiner);
	HashDivider *hd = new HashDivider(numPartitions);
	ShuffledDCUS<K, V, C> *shuffledDCUS = new ShuffledDCUS<K, V, C>(*this, *agg, *hd, xyz_pair_DCUS_combineByKey_inner_hash_f<K, C>, xyz_pair_DCUS_combineByKey_inner_to_string_f<K, C>, xyz_pair_DCUS_combineByKey_inner_from_string_f<K, C>);
	return shuffledDCUS->mapToPair(xyz_pair_DCUS_do_nothing_f<K, C>);
 }

template <class K, class V, class T>
PairDCUS<K, V, Pair<K, V> > & PairDCUS<K, V, T>::reduceByKey(
		Pair<K, V> (*reduce_function)(Pair<K, V>, Pair<K, V>),
		int numPartitions)
{
	return combineByKey(xyz_pair_DCUS_do_nothing_f<K, V>, reduce_function, numPartitions);
}

template <class K, class V, class T>
PairDCUS<K, V, Pair<K, V> > & PairDCUS<K, V, T>::reduceByKey(
		Pair<K, V> (*reduce_function)(Pair<K, V>, Pair<K, V>))
{
	return combineByKey(xyz_pair_DCUS_do_nothing_f<K, V>, reduce_function, (this->context).getTotalThreads());
}

template <class K, class V>
Pair<K, IteratorSeq<V> > xyz_pair_DCUS_groupByKey_inner_createCombiner ( Pair<K, V> p) {
	vector<V> vv;
	vv.push_back(p.v2);
	IteratorSeq<V> iv(vv);
	return Pair<K, IteratorSeq<V> >(p.v1, iv);
}

template <class K, class V>
Pair<K, IteratorSeq<V> > xyz_pair_DCUS_groupByKey_inner_mergeCombiner (
		Pair<K, IteratorSeq<V> > p1,
		Pair<K, IteratorSeq<V> > p2) {
	vector<V> vv1 = p1.v2.getVector();
	vector<V> vv2 = p2.v2.getVector();
	vv1.insert(vv1.end(), vv2.begin(), vv2.end());
	IteratorSeq<V> iv(vv1);
	return Pair<K, IteratorSeq<V> >(p1.v1, iv);
}

template <class K, class V, class T>
PairDCUS<K, IteratorSeq<V>, Pair<K, IteratorSeq<V> > > & PairDCUS<K, V, T>::groupByKey(
		int num_partitions) {
	return combineByKey(xyz_pair_DCUS_groupByKey_inner_createCombiner<K, V>,
			xyz_pair_DCUS_groupByKey_inner_mergeCombiner<K, V>,
			num_partitions);

}

template <class K, class V, class T>
PairDCUS<K, IteratorSeq<V>, Pair<K, IteratorSeq<V> > > & PairDCUS<K, V, T>::groupByKey() {
	return groupByKey((this->context).getTotalThreads());

}

/* inner function for join */
template <class K, class V, class W>
Pair<K, Either<V, W> > xyz_pair_DCUS_join_inner_map_left_f(Pair<K, V> pl) {
	Either<V, W> e;
	e.initLeft(pl.v2);
	return Pair<K, Either<V, W> > (pl.v1, e);
}

template <class K, class V, class W>
Pair<K, Either<V, W> > xyz_pair_DCUS_join_inner_map_right_f(Pair<K, W> pr) {
	Either<V, W> e;
	e.initRight(pr.v2);
	return Pair<K, Either<V, W> > (pr.v1, e);
}

template <class K, class V, class W>
Pair<K, Either<V, W> > xyz_pair_DCUS_join_inner_map_to_pair_f(Pair<K, Either<V, W> > p) {
	return p;
}

template <class K, class V, class W>
vector< Pair< K, Pair< V, W > > > xyz_pair_DCUS_join_inner_flat_map_f(Pair< K, IteratorSeq< Either< V, W > > > ps) {
	vector< Pair< K, Pair< V, W > > > ret;
	vector<V> vv;
	vector<W> vw;
	for (long i=0; i<ps.v2.size(); i++) {
		Either< V, W > ei = ps.v2.at(i);
		if (ei.type == EITHER_TYPE_LEFT) {
			vv.push_back(ei.left);
		} else if (ei.type == EITHER_TYPE_RIGHT) {
			vw.push_back(ei.right);
		}
	}
	for (unsigned int i=0; i<vv.size(); i++) {
		for (unsigned int j=0; j<vw.size(); j++) {
			ret.push_back(Pair< K, Pair< V, W > >(ps.v1, Pair< V, W >(vv[i], vw[j])));
		}
	}

	return ret;
}

template <class K, class V, class T>
template <class W>
PairDCUS< K, Pair< V, W >, Pair< K, Pair< V, W > > > & PairDCUS<K, V, T>::join(
		DCUS< Pair< K, W > > &other,
		int num_partitions) {
	MappedDCUS< Pair<K, Either<V, W> >, Pair<K, V> > &mapDCUS1 = this->map(xyz_pair_DCUS_join_inner_map_left_f<K, V, W>);
	MappedDCUS< Pair<K, Either<V, W> >, Pair<K, W> > &mapDCUS2 = other.map(xyz_pair_DCUS_join_inner_map_right_f<K, V, W>);

	UnionDCUS< Pair<K, Either<V, W> > > &all = mapDCUS1.unionDCUS(&mapDCUS2);
	return all.mapToPair(xyz_pair_DCUS_do_nothing_f< K, Either<V, W> >)
			.groupByKey(num_partitions)
			.flatMap(xyz_pair_DCUS_join_inner_flat_map_f<K, V, W>)
			.mapToPair(xyz_pair_DCUS_do_nothing_f< K, Pair< V, W > >);

}

template <class K, class V, class T>
template <class W>
PairDCUS< K, Pair< V, W >, Pair< K, Pair< V, W > > > & PairDCUS<K, V, T>::join(
		DCUS< Pair< K, W > > &other) {
	return join(other, (this->context).getTotalThreads());
}

#endif /* PIARDCUS_HPP_ */


