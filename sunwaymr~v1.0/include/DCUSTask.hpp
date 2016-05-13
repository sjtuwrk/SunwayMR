/*
 * DCUSTask.hpp
 *
 *  Created on: Dec 4, 2015
 *      Author: yupeng
 */

#ifndef DCUSTASK_HPP_
#define DCUSTASK_HPP_


#include "DCUSTask.h"

#include "Partition.hpp"
#include "DCUS.hpp"
#include "Task.hpp"

template <class T, class U> DCUSTask<T, U>::DCUSTask(DCUS<T> &r, Partition &p)
: DCUS(r), partition(p) {
}

template <class T, class U> DCUSTask<T, U>::~DCUSTask () {

}

template <class T, class U> vector<string> DCUSTask<T, U>::preferredLocations() {
	return DCUS.preferredLocations(partition);
}


#endif /* DCUSTASK_HPP_ */
