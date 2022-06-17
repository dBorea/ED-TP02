#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "ListNode.hpp"

template <typename T>
class List{
	private:
		ListNode<T> *startPtr;
		ListNode<T> *endPtr;
		bool isEmpty();
		void insertBegin(T);
		void insertEnd(T);
	public:
		List();
		~List();
		void insertNewNode(T);
		void print(std::ostream&);
		ListNode<T>* search(T);
};

template <typename T>
List<T>::List(){
	startPtr = nullptr;
	endPtr = nullptr;
}

template <typename T>
List<T>::~List(){
	if(!isEmpty()){
		ListNode<T> *currentPtr;
	}
}

template <typename T>
List<T>::~List(){
	if (!isEmpty()){
      ListNode<T> *currentPtr = startPtr;
      ListNode<T> *tempPtr;

      while ( currentPtr != 0 ){  
         tempPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }
}

template <typename T>
bool List<T>::isEmpty(){
	if(startPtr == NULL && endPtr == NULL)
		return 1;
	else
		return 0;
}

template <typename T>
void List<T>::insertBegin(T dataIn){
	if(isEmpty()){
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		newPtr->nextPtr = startPtr; //the next pointer of the new node points to the node that was previously first
		startPtr = newPtr; //the pointer for the new node is now the starting node
	}
}

template <typename T>
void List<T>::insertEnd(T dataIn){
	if(isEmpty()){
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		endPtr->nextPtr = newPtr; //the current last node's next pointer points to the new node
		endPtr = newPtr; //the new node is now the last node in the list
	}
}

template <typename T>
void List<T>::insertNewNode(T dataIn){
	if(isEmpty()){
		insertBegin(dataIn);
		return;
	} 

	if(dataIn < startPtr->data){
		insertBegin(dataIn);
	} else if(dataIn >= endPtr->data){
		insertEnd(dataIn);
	} else {
		ListNode<T> * currentPtr = startPtr;
		ListNode<T> * newPtr = new ListNode<T>(dataIn);
		for(; currentPtr != endPtr ;){
			if((newPtr->data < currentPtr->nextPtr->data) && (newPtr->data >= currentPtr->data)){
				ListNode<T> *next = currentPtr->nextPtr;
				currentPtr->nextPtr = newPtr;
				newPtr->nextPtr = next;
				break;
			}
			currentPtr = currentPtr->nextPtr;
		}
	}

}

template <typename T>
void List<T>::print(std::ostream& output){
	if(isEmpty()){
		std::cout << "Tentativa de impressão com lista vazia" << endl;
	} else {
		ListNode<T> *currentPtr = startPtr;
		for(; currentPtr != nullptr ;){
			output << currentPtr->data << std::endl;
			currentPtr = currentPtr->nextPtr;
		}
	}
}

template <typename T>
ListNode<T>* List<T>::search(T key){
	ListNode<T>* nodePtr;
	bool found = false;

	nodePtr = startPtr;

	for(; (!found) && (nodePtr != nullptr) ;){
		if(nodePtr->data == key)
			found = true;
		else
			nodePtr = nodePtr->nextPtr;
	}

	return nodePtr;
}


#endif