/*
 * DCUSTask.h
 *
 * Super class of Task classes, with &DCUS and &partition as members.
 *
 *  Created on: Dec 2, 2015
 *      Author: yupeng
 */

#ifndef DCUSTASK_H_
#define DCUSTASK_H_

#include <vector>
#include <string>

#include "Partition.h"
#include "DCUS.h"
#include "Task.h"
using std::vector;
using std::string;


template <class T, class U>
class DCUSTask: public Task<U> {
public:
	DCUSTask(DCUS<T> &r, Partition &p);
	virtual ~DCUSTask();
	virtual U& run() = 0;
	virtual string serialize(U &t) = 0;
	virtual U& deserialize(string s) = 0;
	virtual vector<string> preferredLocations();

	DCUS<T> &DCUS;
	Partition &partition;
};


#endif /* DCUSTASK_H_ */
