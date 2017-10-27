/*
 * Aggregator.hpp
 *

 */



#ifndef INCLUDE_AGGREGATOR_HPP_
#define INCLUDE_AGGREGATOR_HPP_

#include "Aggregator.h"

template <class V, class C>
Aggregator<V, C>::Aggregator(C (*cc)(V&), C (*mc)(C&, C&))
{
	createCombiner = cc;
	mergeCombiners = mc;
}

#endif /* INCLUDE_AGGREGATOR_HPP_ */
