/*
 * CollectTask.h
 *
 * DCUS::collect() will run CollectTasks
 *
 */

#ifndef COLLECT_H_
#define COLLECT_H_

#include "DCUSTask.h"

#include <vector>
using namespace std;

template <class T>
class CollectTask : public DCUSTask< T, vector<T> >
{
public:
	    CollectTask(DCUS<T> &r, Partition &p);
		vector<T>& run();
		string serialize(vector<T> &t);
		vector<T>& deserialize(string s);

private:
};

#endif
