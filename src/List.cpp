#include "List.hpp"

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

// INSERTION METHODS

void List::insertBegin(RankedString dataIn){
	ListNode * newPtr = new ListNode(dataIn);
	if(isEmpty()){
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		newPtr->nextPtr = startPtr; //the next pointer of the new node points to the node that was previously first
		startPtr = newPtr; //the pointer for the new node is now the starting node
	}
	escreveMemLog((long int)(&(newPtr->nextPtr)), sizeof(ListNode*), 1);
	listSize++;
}

void List::insertEnd(RankedString dataIn){
	ListNode * newPtr = new ListNode(dataIn);
	if(isEmpty()){
		startPtr = newPtr;
		endPtr = newPtr;
	} else {
		endPtr->nextPtr = newPtr; //the current last node's next pointer points to the new node
		endPtr = newPtr; //the new node is now the last node in the list
	}
	escreveMemLog((long int)(&(newPtr->nextPtr)), sizeof(ListNode*), 1);
	listSize++;
}

void List::insertNewNode(RankedString dataIn){
	if(isEmpty()){
		insertBegin(dataIn);
		return;
	} 

	if(dataIn < startPtr->getData()){
		insertBegin(dataIn);
	} else if(dataIn > endPtr->getData()){
		insertEnd(dataIn);
	} else {
		ListNode * currentPtr = startPtr;
		ListNode * newPtr = new ListNode(dataIn);
		for(; currentPtr != endPtr ;){
			if(currentPtr->getData() == newPtr->getData()){
				currentPtr->getData().increment();
				leMemLog((long int)(&(currentPtr->getData())), sizeof(RankedString), 0);
			}
			if((newPtr->getData() < currentPtr->nextPtr->getData()) && (newPtr->getData() > currentPtr->getData())){
				newPtr->nextPtr = currentPtr->nextPtr;
				leMemLog((long int)(&(currentPtr->nextPtr)), sizeof(ListNode*), 1);
				escreveMemLog((long int)(&(currentPtr->nextPtr)), sizeof(ListNode*), 1);
				currentPtr->nextPtr = newPtr;
				break;
			}
			leMemLog((long int)(&(currentPtr->nextPtr)), sizeof(ListNode*), 1);
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
			output << currentPtr->getData() << std::endl;
			leMemLog((long int)(&(currentPtr->nextPtr)), sizeof(ListNode*), 1);
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
		if(nodePtr->getData().getPalavra() == key)
			found = true;
		else{
			leMemLog((long int)(&(nodePtr->nextPtr)), sizeof(ListNode*), 1);
			nodePtr = nodePtr->nextPtr;
		}
	}

	return nodePtr;
}

void List::updateOrder(CustomAlphaCmp* orderPtr){
	ListNode* nodePtr;
	nodePtr = startPtr;

	for(; nodePtr != nullptr ;){
		nodePtr->getData().setOrder(orderPtr);
		leMemLog((long int)(&(nodePtr->nextPtr)), sizeof(ListNode*), 1);
		nodePtr = nodePtr->nextPtr;
	}
}

// SORTING METHODS

void List::sortList(){
	startPtr = quickSortHibrido(startPtr, endPtr);
	endPtr = getUltimo(startPtr);
}

ListNode* List::getUltimo(ListNode* atual){
	for(; atual != nullptr  && atual->nextPtr != nullptr ;){
		leMemLog((long int)(&(atual->nextPtr)), sizeof(ListNode*), 1);
		atual = atual->nextPtr;
	}
	return atual;
}

ListNode* List::particao(ListNode* head, ListNode* end, ListNode** newHead, ListNode** newEnd){
	ListNode* pivo;
	ListNode* anterior = nullptr, *atual = head;

	if(pivotArg > 0){
		pivo = head;
		for(int i=0; i<pivotArg && pivo->nextPtr != nullptr; i++){
			leMemLog((long int)(&(pivo->nextPtr)), sizeof(ListNode*), 1);
			pivo = pivo->nextPtr;
		}
		atual = quickSortHibrido(head, pivo);
		pivo = atual;
		for(int i=0; i<pivotArg/2 && pivo->nextPtr != nullptr; i++){
			leMemLog((long int)(&(pivo->nextPtr)), sizeof(ListNode*), 1);
			pivo = pivo->nextPtr;
		}
	}
	else { pivo = end; }
	ListNode* cauda = pivo;

	for(;atual != pivo;){
		if(atual->getData() < pivo->getData()){
			if((*newHead) == nullptr) (*newHead) = atual;

			anterior = atual;
			leMemLog((long int)(&(atual->nextPtr)), sizeof(ListNode*), 1);
			atual = atual->nextPtr;
		} 
		else {
			if(anterior) {
				leMemLog((long int)(&(atual->nextPtr)), sizeof(ListNode*), 1);
				anterior->nextPtr = atual->nextPtr;
			}
			ListNode* tmp = atual->nextPtr;
			atual->nextPtr = nullptr;
			cauda->nextPtr = atual;
			cauda = atual;
			atual = tmp;

			escreveMemLog((long int)(&(atual->nextPtr)), sizeof(ListNode*), 1);
			escreveMemLog((long int)(&(cauda->nextPtr)), sizeof(ListNode*), 1);
		}
	}

	if((*newHead) == nullptr)
		*newHead = pivo;

	(*newEnd) = cauda;

	return pivo;
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
			for(; tmp->nextPtr != pivo ;){
				leMemLog((long int)(&(tmp->nextPtr)), sizeof(ListNode*), 1);
				tmp = tmp->nextPtr;
			}
			tmp->nextPtr = nullptr;

			newHead = quickSortHibrido(newHead, tmp);

			tmp = getUltimo(newHead);
			tmp->nextPtr = pivo;
			escreveMemLog((long int)(&(tmp->nextPtr)), sizeof(ListNode*), 1);
		}

		pivo->nextPtr = quickSortHibrido(pivo->nextPtr, newEnd);
		escreveMemLog((long int)(&(pivo->nextPtr)), sizeof(ListNode*), 1);

		return newHead;
	}
}
