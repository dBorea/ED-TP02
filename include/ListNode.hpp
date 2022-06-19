#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "msgassert.hpp"
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
	friend void sortedInsert(ListNode *, ListNode **);
	friend void insertionSort(ListNode **, ListNode*);
	friend int nodeDistance(ListNode *, ListNode *);
	friend class List;
};

ListNode::ListNode(RankedString inputData){
	data = inputData;
	nextPtr = nullptr;
}

RankedString ListNode::getData(){
	return data;
}

void sortedInsert(ListNode *newnode, ListNode **sorted){
	if ((*sorted) == nullptr || (*sorted)->getData() >= newnode->getData()){
		newnode->nextPtr = (*sorted);
		(*sorted) = newnode;
	}
	else{
		ListNode *current = (*sorted);
		// Locate the node before the point of insertion
		for (; current->nextPtr != nullptr && (newnode->data > current->nextPtr->data);)
			current = current->nextPtr;

		newnode->nextPtr = current->nextPtr;
		current->nextPtr = newnode;
	}
}

void insertionSort(ListNode **head, ListNode *end){
	ListNode *sorted = nullptr;
	ListNode *current = *head;

	for (; current != end && current != nullptr ;){
		ListNode *next = current->nextPtr;

		sortedInsert(current, &sorted);

		current = next;
	}

	*head = sorted;
}

int nodeDistance(ListNode *head, ListNode *end){
	erroAssert(head != nullptr && end != nullptr, "Chamada inválida de nodeDistance");
	
	int distance = 0;
	for(ListNode *current = head; current != end; current = current->nextPtr){
		erroAssert(current->nextPtr != nullptr, "Chamada de nodeDistance com lista fraturada");
		distance++;
	}
	
	return distance;
}

#endif