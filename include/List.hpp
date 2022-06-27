#ifndef LIST_H
#define LIST_H

#include "ListNode.hpp"

#define INSERTION_THRESHOLD 5

class List{
	private:
		ListNode *startPtr;
		ListNode *endPtr;
		int listSize;
		int insertionThreshold;
		int pivotArg;

		bool isEmpty();

		ListNode* getUltimo(ListNode*);
		ListNode* particao(ListNode*, ListNode*, ListNode**, ListNode**);

		ListNode* quickSortHibrido(ListNode*, ListNode*);

	public:
		List();
		~List();
		int getSize();
		void setInsertionTreshold(int);
		void setPivotArg(int);
		void insertBegin(RankedString);
		void insertEnd(RankedString);
		void insertNewNode(RankedString);
		void printToOutput(std::ostream&);
		ListNode* search(std::string);
		void updateOrder(CustomAlphaCmp*);
		void sortList();
};

#endif