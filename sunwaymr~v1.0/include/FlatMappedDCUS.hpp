/*
 * FlatMapppedDCUS.hpp
 *
 *  Created on: Jan 13, 2016
 *      Author: yupeng
 */

#ifndef FLATMAPPEDDCUS_HPP_
#define FLATMAPPEDDCUS_HPP_


#include "FlatMappedDCUS.h"

#include <iostream>
#include "IteratorSeq.hpp"
#include "Partition.hpp"
#include "DCUS.hpp"
using namespace std;

template <class U, class T>
FlatMappedDCUS<U, T>::FlatMappedDCUS(DCUS<T> &prev, vector<U> (*f)(T))
:DCUS<U>::DCUS(prev.context), prevDCUS(prev)
{
	mappedFunction = f;
}

template <class U, class T>
void FlatMappedDCUS<U, T>::shuffle()
{
	prevDCUS.shuffle();
}

template <class U, class T>
vector<Partition*> FlatMappedDCUS<U, T>::getPartitions()
{
	return prevDCUS.getPartitions();
}

template <class U, class T>
vector<string> FlatMappedDCUS<U, T>::preferredLocations(Partition &p)
{
	return prevDCUS.preferredLocations(p);
}

template <class U, class T>
IteratorSeq<U>  FlatMappedDCUS<U, T>::iteratorSeq(Partition &p)
{
	IteratorSeq<T> seq1 = prevDCUS.iteratorSeq(p);
	return seq1.flatMap(mappedFunction);
}


#endif /* FLATMAPPEDDCUS_HPP_ */



