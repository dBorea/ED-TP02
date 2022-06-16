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
		void print();
		ListNode<T>* search(T);
};


#endif