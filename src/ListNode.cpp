#include "ListNode.hpp"

ListNode::ListNode(RankedString inputData){
	escreveMemLog((long int)(&data), sizeof(RankedString), 0);
	data = inputData;
	escreveMemLog((long int)(&nextPtr), sizeof(ListNode*), 0);
	nextPtr = nullptr;
}

RankedString& ListNode::getData(){
	leMemLog((long int)(&data), sizeof(RankedString), 0);
	return data;
}

void ListNode::incrementaData(){
	data.increment();
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

	for (; end->nextPtr != current && current != nullptr ;){
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