#ifndef SLL_H
#define SLL_H
#include <iostream>
using namespace std;

template <class T> class ListNode {
public:
	T data;
	ListNode *next;
	ListNode(T val);
};

template <class T> class LinkedList {
public:
	LinkedList();
	~LinkedList();
	ListNode<T> *start; // special variable which stores address of the head node.
	ListNode<T> *pLoc; // to be used by Search(value) method to store address
	ListNode<T> *loc; // to be used by Search(value) method to store 
	int length;
	void insert(T);
	void printList();
	void destroyData();
	bool search(T value);
    // address of the node containing the searched value in alist.If it is not
	// found it contains NULL.
};

template <class T> ListNode<T>::ListNode(T val) {
	// Initializing ListNode
	data = val;
	next = NULL;
}

template <class T> LinkedList<T>::LinkedList() {
	// Init Linked List
	start = NULL;
	pLoc = NULL;
	loc = NULL;
	length = 0;
}

template <class T> LinkedList<T>::~LinkedList() {
	// Deleting All Nodes on List Destruction
	if (start == NULL) return;
	ListNode<T> *tempNode = start;
	// iterating over the entire list and deleting nodes
	while (tempNode) {
		pLoc = tempNode;
		tempNode = tempNode->next;
		delete pLoc;
	}
	start = NULL;
}

template <class T> bool LinkedList<T>::search(T value) {
	if (start == NULL) return false;
	ListNode<T> *tempNode = start;
	// iterating over the entire list and deleting nodes
	while (tempNode) {
		if (tempNode->data == value) return true;
		pLoc = tempNode;
		tempNode = tempNode->next;
	}

	return false;
}

template <class T> void LinkedList<T>::insert(T value) {
	if (search(value)) return;
	ListNode<T> *newNode = new ListNode<T>(value);
	// if list empty, adding a new node and updating start and last equal to
	// newnode
	if (start == NULL) start = newNode;
	// if list not previously empty, adding node and updating start
	else if (start) {
		newNode->next = start;
		start = newNode;
	}

	length++;
}

template <class T> void LinkedList<T>::printList() {
	ListNode<T> *node = start;
	while (node)
    {
		cout << node->data->name << ", ";
		node = node->next;
	}
	cout << endl;
}

template <class T> void LinkedList<T>::destroyData() {
		// Deleting All Nodes on List Destruction
	if (!start) return;
	ListNode<T> *tempNode = start;
	// iterating over the entire list and deleting nodes
	while (tempNode) {
		pLoc = tempNode;
		tempNode = tempNode->next;
		if (pLoc->data) {
			delete pLoc->data;
			pLoc->data = NULL;
		}
	}
}

#endif