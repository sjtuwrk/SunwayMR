#ifndef PARALLELARRAYPARTITION_HPP_
#define PARALLELARRAYPARTITION_HPP_


#include "ParallelArrayPartition.h"

#include <iostream>

#include "IteratorSeq.hpp"
#include "Partition.hpp"
using namespace std;

template <class T>
ParallelArrayPartition<T>::ParallelArrayPartition(long _DCUSID, int _partitionID, IteratorSeq<T> &_values) 
: DCUSID(_DCUSID), partitionID(_partitionID), values(_values)
{
}

template <class T>
IteratorSeq<T> ParallelArrayPartition<T>::iteratorSeq()
{
	return values;
}



#endif /* PARALLELARRAYPARTITION_HPP_ */
