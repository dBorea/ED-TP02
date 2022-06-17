#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "RankedString.hpp"

class ListNode{
	private:
		RankedString data;
		ListNode *nextPtr;
	public:
		ListNode(RankedString);
		RankedString getData();
		void incrementaData(){
			data.increment();
		}
	friend class List;
};

ListNode::ListNode(RankedString inputData){
	data = inputData;
	nextPtr = nullptr;
}

RankedString ListNode::getData(){
	return data;
}

#endif