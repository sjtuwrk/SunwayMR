#ifndef MAPPEDDCUS_HPP_
#define MAPPEDDCUS_HPP_


#include "MappedDCUS.h"

#include <iostream>
#include "IteratorSeq.hpp"
#include "Partition.hpp"
#include "DCUS.hpp"
using namespace std;

template <class U, class T>
MappedDCUS<U, T>::MappedDCUS(DCUS<T> &prev, U (*f)(T))
:DCUS<U>::DCUS(prev.context), prevDCUS(prev)
{
	mappedFunction = f;
}

template <class U, class T>
void MappedDCUS<U, T>::shuffle()
{
	prevDCUS.shuffle();
}

template <class U, class T>
vector<Partition*> MappedDCUS<U, T>::getPartitions()
{
	return prevDCUS.getPartitions();
}

template <class U, class T>
vector<string> MappedDCUS<U, T>::preferredLocations(Partition &p)
{
	return prevDCUS.preferredLocations(p);
}

template <class U, class T>
IteratorSeq<U>  MappedDCUS<U, T>::iteratorSeq(Partition &p)
{
	IteratorSeq<T> seq1 = prevDCUS.iteratorSeq(p);
	return seq1.map(mappedFunction);
}


#endif /* MAPPEDDCUS_HPP_ */
