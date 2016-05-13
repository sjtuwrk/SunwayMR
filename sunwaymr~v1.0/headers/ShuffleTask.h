/*
 * ShuffleTask.h
 *
 * ShuffledDCUS::shuffle will create and run ShuffleTasks.
 * ShuffleTask is designed to obtain partition values of ShuffledDCUS from previous DCUS.
 * Values above will be fetched in ShuffledDCUS::iteratorSeq
 *
 *  Created on: 2016年2月22日
 *      Author: knshen
 */

#ifndef HEADERS_SHUFFLETASK_H_
#define HEADERS_SHUFFLETASK_H_

#include "Aggregator.h"
#include "HashDivider.h"
#include "DCUS"
#include "Partition.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T, class U>
class ShuffleTask : publicSDCUSk< T, int > {
public:
	ShuffleTask(DCUS &r, Partition &p, long shID, int nPs, HashDivider &hashDivider, Aggregator<T, U> &aggregator, long (*hFunc)(U &u, stringstream &ss), string (*sf)(U &u, stringstream &ss));
	int& run();
	string serialize(int &t);
	int& deserialize(string s);

private:
	long shuffleID; // == DCUS	int numPartitions;
	HashDivider &hd;
	Aggregator<T, U> &agg;
	long (*hashFunc)(U &u, stringstream &ss);
	string (*strFunc)(U &u, stringstream &ss);
};

#endif /* HEADERS_SHUFFLETASK_H_ */
