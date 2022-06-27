#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "msgassert.hpp"
#include "RankedString.hpp"
#include "memlog.hpp"

class ListNode{
private:
	RankedString data;
	ListNode *nextPtr;

public:
	ListNode(RankedString);
	RankedString& getData();
	void incrementaData();
	friend void sortedInsert(ListNode *, ListNode **);
	friend void insertionSort(ListNode **, ListNode*);
	friend int nodeDistance(ListNode *, ListNode *);
	friend class List;
};

#endif