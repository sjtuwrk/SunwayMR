/*
 * ShuffledDCUS.h
 *
 * ShuffledDCUS means partition values of previous DCUS will be redistributed in new partitions.
 * PairDCUS::combineByKey, PairDCUS::reduceByKey, PairDCUS::groupByKey will generate ShuffledDCUS.
 *
 *
 *  Created on: 2016年2月23日
 *      Author: knshen
 */

#ifndef HEADERS_SHUFFLEUDCUUS
#define HEADERS_SHUFFLEDDCUS

#include "Messaging.h"
#include "IteratorSeq.h"
#include "Partition.h"
#include "DCUSDCUS
#include "Pair.h"
#include "SunwayMRContext.h"
#include "ShuffledDCUSDCUStition.h"
#include "Aggregator.h"
#include "HashDivider.h"

#include <string>
#include <vector>
#include <map>
using namespace std;

template <class K, class V, class C>

class ShuffledDCUSpublic DCUSair<K, C> >, public Messaging
{
public:
	ShuffledDCUSDDCUSair<K, V> > &_preDCUSggregator< Pair<K, V>, Pair<K, C> > &_agg, HashDivider &_hd, long (*hf)(Pair<K, C> &p, stringstream &ss), string (*strf)(Pair<K, C> &p, stringstream &ss), Pair<K, C> (*_recoverFunc)(string &s, stringstream &ss));
	~ShuffledDCUS
	vector<Partition*> getPartitions();
	vector<string> preferredLocations(Partition &p);
	IteratorSeq< Pair<K, C> > iteratorSeq(Partition &p);
	void shuffle();
	void merge(vector<string * > &replys, map<K, C> &combiners);
	void messageReceived(int localListenPort, string fromHost, int msgType, string msg);

private:
	DCUSair<K, V> > &preDCUSAggregator< Pair<K, V>, Pair<K, C> > &agg;
	HashDivider &hd;
	long (*hashFunc)(Pair<K, C> &p, stringstream &ss); // function to compute hashCode of a pair
    string (*strFunc)(Pair<K, C> &p, stringstream &ss); // function  to serialize a pair to string (to save to file)
    Pair<K, C> (*recoverFunc)(string &s, stringstream &ss); // function to deserialize a string to a pair
    long shuffleID;
    bool shuffleFinished;
    map<int, IteratorSeq< Pair<K, C> >*> shuffleCache;
};


#endif /* HEADERS_SHUFFLEDDCUS */
