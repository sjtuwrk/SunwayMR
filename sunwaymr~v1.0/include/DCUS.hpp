#ifndef DCUS_HPP_
#define DCUS_HPP_

#include "DCUS.h"

#include <iostream>
#include <sstream>

#include "ReduceTask.hpp"
#include "Task.hpp"
#include "TaskResult.hpp"
#include "IteratorSeq.hpp"
#include "MappedDCUS.hpp"
#include "FlatMappedDCUS.hpp"
#include "PairDCUS.hpp"
#include "Partition.hpp"
#include "SunwayMRContext.hpp"
#include "Logging.hpp"
#include "CollectTask.hpp"
#include "ShuffleTask.hpp"
#include "Pair.hpp"
#include "UnionDCUS.hpp"
using namespace std;

template <class T>
DCUS<T>::DCUS(SunwayMRContext &c)
: context(c)
{
	DCUSID = XYZ_CURRENT_DCUS_ID++;
}

template <class T>
DCUS<T> & DCUS<T>::operator=(const DCUS<T> &p) {
	this->initDCUSFrom(p);
	return *this;
}

template <class T>
DCUS<T>::~DCUS()
{

}

template <class T>
void DCUS<T>::initDCUSFrom(const DCUS<T> &r) {
	this->context = r.context;
	this->partitions = r.partitions;
	this->DCUSID = r.DCUSID;
}

template <class T> template <class U>
MappedDCUS<U, T> & DCUS<T>::map(U (*f)(T))
{
	MappedDCUS<U, T> *map_DCUS = new MappedDCUS<U, T>(*this, f);
	return *map_DCUS;
}

template <class T> template <class U>
FlatMappedDCUS<U, T> & DCUS<T>::flatMap(vector<U> (*f)(T))
{
	FlatMappedDCUS<U, T> *map_DCUS = new FlatMappedDCUS<U, T>(*this, f);
	return *map_DCUS;
}

template <class T>
void DCUS<T>::shuffle()
{
	// do nothing
}

template <class T> template <class K, class V>
PairDCUS<K, V, T> & DCUS<T>::mapToPair(Pair<K, V> (*f)(T))
{
	PairDCUS<K, V, T> *pair_DCUS = new PairDCUS<K, V, T>(*this, f);
	return *pair_DCUS;
}

template <class T>
T DCUS<T>::reduce(T (*g)(T, T))
{
	shuffle();
	// construct tasks
	vector< Task< vector<T> >* > tasks;
	vector<Partition*> pars = this->getPartitions();

	for (unsigned int i = 0; i < pars.size(); i++)
	{
		Task< vector<T> > *task = new ReduceTask<T>(*this, *(pars[i]), g);
		tasks.push_back(task);
	}

	// run tasks via context
	vector< TaskResult< vector<T> >* > results = this->context.runTasks(tasks);

	//get results
	vector<T> values_results;
	for (unsigned int j = 0; j < results.size(); j++)
		if(results[j]->value.size() > 0) {
			values_results.push_back(results[j]->value[0]);
		}

	if (values_results.size() == 0)
	{
		//should do logging
		Logging::logWarning("DCUS: reduce received empty results collection!!!");
		return 0;
	}
	//reduce left results
	IteratorSeq<T> it(values_results);
	return it.reduceLeft(g)[0];
}

template <class T>
Pair< T, int > distinct_inner_map_to_pair_f (T t) {
	return Pair< T, int >(t, 0);
}

template <class T>
Pair< T, int> distinct_inner_reduce_f (Pair< T, int > p1, Pair< T, int > p2) {
	return Pair< T, int >(p1.v1, 0);
}

template <class T>
long distinct_inner_hash_f (Pair< T, int > p) {
	stringstream ss;
	ss << p.v1;
	return hash(ss.str());
}

template <class T>
string distinct_inner_toString_f (Pair< T, int > p) {
	stringstream ss;
	ss << p;
	return ss.str();
}

template <class T>
Pair< T, int > distinct_inner_fromString_f (string s) {
	Pair< T, int > p;
	stringstream ss(s);
	ss >> p;
	return p;
}

template <class T>
T distinct_inner_map_f (Pair< T, int > p) {
	return p.v1;
}

template <class T>
MappedDCUS<T, Pair< T, int > > & DCUS<T>::distinct(int newNumSlices) {
    //map(x => (x, null)).reduceByKey((x, y) => x, numPartitions).map(_._1)
	return this->mapToPair(distinct_inner_map_to_pair_f<T>)
			.reduceByKey(distinct_inner_reduce_f<T>, newNumSlices)
			.map(distinct_inner_map_f<T>);
}

template <class T>
MappedDCUS<T, Pair< T, int > > & DCUS<T>::distinct() {
	return this->distinct(this->getPartitions().size());
}

template <class T>
vector<T>& DCUS<T>::collect()
{
	shuffle();
	vector<T> *ret = new vector<T>;
	// construct tasks
	vector< Task< vector<T> >* > tasks;
	vector<Partition*> pars = this->getPartitions();
	for(unsigned int i=0; i<pars.size(); i++)
	{
		Task< vector<T> > *task = new CollectTask<T>(*this, *(pars[i]));
		tasks.push_back(task);
	}
	// run tasks via context
	vector< TaskResult< vector<T> >* > results = this->context.runTasks(tasks);
	//get results
	for(unsigned int i=0; i<results.size(); i++)
	{
		for(unsigned int j=0; j<(results[i]->value).size(); j++)
		{
			ret->push_back((results[i]->value)[j]);
		}
	}
	return *ret;
}

template <class T>
UnionDCUS<T> & DCUS<T>::unionDCUS(DCUS<T> *other) {
	vector< DCUS<T>* > DCUSs;
	DCUSs.push_back(this);
	DCUSs.push_back(other);
	UnionDCUS<T> *ret = new UnionDCUS<T>(this->context, DCUSs);
	return *ret;
}

#endif /* DCUS_HPP_ */
