#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class List;

template <typename T>
class ListNode{
	private:
		T data;
		ListNode *nextPtr;
	public:
		ListNode(T);
		T getData();
	friend class List<T>;
};

template <typename T>
ListNode<T>::ListNode(T inputData){
	data = inputData;
	nextPtr = nullptr;
}

template <typename T>
T ListNode<T>::getData(){
	return data;
}

#endif