#ifndef LIST_H
#define LIST_H

#include "ListNode.hpp"

#define INSERTION_THRESHOLD 10

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
		ListNode* QSrecursive(ListNode*, ListNode*);

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

List::List(){
	startPtr = nullptr;
	endPtr = nullptr;
	listSize = 0;
	insertionThreshold = 0;
	pivotArg = 0;
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

int List::getSize(){
	return listSize;
}

void List::setInsertionTreshold(int threshold){
	insertionThreshold = threshold;
}

void List::setPivotArg(int pivot){
	pivotArg = pivot;
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
	listSize++;
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
	listSize++;
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
				newPtr->nextPtr = currentPtr->nextPtr;
				currentPtr->nextPtr = newPtr;
				break;
			}
			currentPtr = currentPtr->nextPtr;
		}
		listSize++;
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
		output << "#FIM" << std::endl;
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
	startPtr = quickSortHibrido(startPtr, endPtr);
	endPtr = getUltimo(startPtr);
}

ListNode* List::getUltimo(ListNode* atual){
	for(; atual != nullptr  && atual->nextPtr != nullptr ;)
		atual = atual->nextPtr;
	return atual;
}

ListNode* List::particao(ListNode* head, ListNode* end, ListNode** newHead, ListNode** newEnd){
	ListNode* pivo;
	if(pivotArg > 0){
		pivo = head;
		for(int i=0; i<pivotArg/2 && pivo->nextPtr != nullptr; i++){
			pivo = pivo->nextPtr;
		}
	}
	else { pivo = end; }
	ListNode* anterior = nullptr, *atual = head, *cauda = pivo;

	for(;atual != pivo;){
		if(atual->data < pivo->data){
			if((*newHead) == nullptr) (*newHead) = atual;

			anterior = atual;
			atual = atual->nextPtr;
		} 
		else {
			if(anterior) anterior->nextPtr = atual->nextPtr;
			ListNode* tmp = atual->nextPtr;
			atual->nextPtr = nullptr;
			cauda->nextPtr = atual;
			cauda = atual;
			atual = tmp;
		}
	}

	if((*newHead) == nullptr)
		*newHead = pivo;

	(*newEnd) = cauda;

	return pivo;
}

ListNode* List::QSrecursive(ListNode* head, ListNode* end){
	if(!head || head == end)
		return head;

	ListNode* newHead = nullptr, *newEnd = nullptr;

	ListNode* pivo = particao(head, end, &newHead, &newEnd);

	if(newHead != pivo){
		ListNode* tmp = newHead;
		for(; tmp->nextPtr != pivo ;)
			tmp = tmp->nextPtr;
		tmp->nextPtr = nullptr;

		newHead = QSrecursive(newHead, tmp);

		tmp = getUltimo(newHead);
		tmp->nextPtr = pivo;
	}

	pivo->nextPtr = QSrecursive(pivo->nextPtr, newEnd);

	return newHead;
}

ListNode* List::quickSortHibrido(ListNode* head, ListNode* end){
	if(!head || head == end)
		return head;
	
	if(nodeDistance(head, end) + 1 < insertionThreshold){
		insertionSort(&head, end);
		return head;
	}
	else {
		ListNode* newHead = nullptr, *newEnd = nullptr;
		ListNode* pivo = particao(head, end, &newHead, &newEnd);

		if(newHead != pivo){
			ListNode* tmp = newHead;
			for(; tmp->nextPtr != pivo ;)
				tmp = tmp->nextPtr;
			tmp->nextPtr = nullptr;

			newHead = QSrecursive(newHead, tmp);

			tmp = getUltimo(newHead);
			tmp->nextPtr = pivo;
		}

		pivo->nextPtr = QSrecursive(pivo->nextPtr, newEnd);

		return newHead;
	}
	
}

#endif