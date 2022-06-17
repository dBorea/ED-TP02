#ifndef LIST_H
#define LIST_H

#include "ListNode.hpp"

class List{
	private:
		ListNode *startPtr;
		ListNode *endPtr;
		bool isEmpty();

		ListNode* SortedMerge(ListNode*, ListNode*);
		void FrontBackSplit(ListNode* , ListNode** , ListNode**);
		void MergeSort(ListNode**);

	public:
		List();
		~List();
		void insertBegin(RankedString);
		void insertEnd(RankedString);
		void insertNewNode(RankedString);
		void printToOutput(std::ostream&);
		ListNode* search(std::string);
		void updateOrder(CustomAlphaCmp*);
		void sortList();
};

List::List(){
	startPtr = nullptr;
	endPtr = nullptr;
}

List::~List(){
	if (!isEmpty()){
      ListNode *currentPtr = startPtr;
      ListNode *tempPtr;

      while ( currentPtr != 0 ){  
         tempPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }
}

bool List::isEmpty(){
	if(startPtr == NULL && endPtr == NULL)
		return 1;
	else
		return 0;
}

void List::insertBegin(RankedString dataIn){
	if(isEmpty()){
		ListNode * newPtr = new ListNode(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		ListNode * newPtr = new ListNode(dataIn);
		newPtr->nextPtr = startPtr; //the next pointer of the new node points to the node that was previously first
		startPtr = newPtr; //the pointer for the new node is now the starting node
	}
}

void List::insertEnd(RankedString dataIn){
	if(isEmpty()){
		ListNode * newPtr = new ListNode(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		ListNode * newPtr = new ListNode(dataIn);
		endPtr->nextPtr = newPtr; //the current last node's next pointer points to the new node
		endPtr = newPtr; //the new node is now the last node in the list
	}
}

void List::insertNewNode(RankedString dataIn){
	if(isEmpty()){
		insertBegin(dataIn);
		return;
	} 

	if(dataIn < startPtr->data){
		insertBegin(dataIn);
	} else if(dataIn > endPtr->data){
		insertEnd(dataIn);
	} else {
		ListNode * currentPtr = startPtr;
		ListNode * newPtr = new ListNode(dataIn);
		for(; currentPtr != endPtr ;){
			if(currentPtr->data == newPtr->data){
				currentPtr->data.increment();
			}
			if((newPtr->data < currentPtr->nextPtr->data) && (newPtr->data > currentPtr->data)){
				ListNode *next = currentPtr->nextPtr;
				currentPtr->nextPtr = newPtr;
				newPtr->nextPtr = next;
				break;
			}
			currentPtr = currentPtr->nextPtr;
		}
	}

}

void List::printToOutput(std::ostream& output){
	if(isEmpty()){
		std::cout << "Tentativa de impressão com lista vazia" << std::endl;
	} else {
		ListNode *currentPtr = startPtr;
		for(; currentPtr != nullptr ;){
			output << currentPtr->data << std::endl;
			currentPtr = currentPtr->nextPtr;
		}
		output << "#FIM";
	}
}

ListNode* List::search(std::string key){
	ListNode* nodePtr;
	bool found = false;

	nodePtr = startPtr;

	for(; (!found) && (nodePtr != nullptr) ;){
		if(nodePtr->data.getPalavra() == key)
			found = true;
		else
			nodePtr = nodePtr->nextPtr;
	}

	return nodePtr;
}

void List::updateOrder(CustomAlphaCmp* orderPtr){
	ListNode* nodePtr;
	nodePtr = startPtr;

	for(; nodePtr != nullptr ;){
		nodePtr->data.setOrder(orderPtr);
		nodePtr = nodePtr->nextPtr;
	}
}

void List::sortList(){
	MergeSort(&startPtr);
}


void List::MergeSort(ListNode** headRef){
    ListNode* head = *headRef;
    ListNode* a;
    ListNode* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == nullptr) || (head->nextPtr == nullptr)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
 
ListNode* List::SortedMerge(ListNode* a, ListNode* b){
    ListNode* result = nullptr;
 
    /* Base cases */
    if (a == nullptr)
        return (b);
    else if (b == nullptr)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->data <= b->data) {
        result = a;
        result->nextPtr = SortedMerge(a->nextPtr, b);
    }
    else {
        result = b;
        result->nextPtr = SortedMerge(a, b->nextPtr);
    }
    return (result);
}

void List::FrontBackSplit(ListNode* source, ListNode** frontRef, ListNode** backRef){
    ListNode* fast;
    ListNode* slow;
    slow = source;
    fast = source->nextPtr;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != nullptr) {
        fast = fast->nextPtr;
        if (fast != NULL) {
            slow = slow->nextPtr;
            fast = fast->nextPtr;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->nextPtr;
    slow->nextPtr = NULL;
}

#endif