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
	ListNode<T> *last; // special variable which stores address of the last node.
	ListNode<T> *pLoc; // to be used by Search(value) method to store address
	ListNode<T> *loc; // to be used by Search(value) method to store 
	void insert(T);
	void printList();
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
	start = last = pLoc = loc = NULL;
}

template <class T> LinkedList<T>::~LinkedList() {
	// Deleting All Nodes on List Destruction
	if (!start) return;
	ListNode<T> *tempNode = start;
	// iterating over the entire list and deleting nodes
	while (tempNode) {
		pLoc = tempNode;
		tempNode = tempNode->next;
		delete pLoc;
	}
	start = last = NULL;
}

template <class T> void LinkedList<T>::insert(T value) {
	ListNode<T> *newNode = new ListNode<T>(value);
	// if list empty, adding a new node and updating start and last equal to
	// newnode
	if (start == NULL) start = last = newNode;
	// if list not previously empty, adding node and updating start
	else if (start) {
		newNode->next = start;
		start = newNode;
	}
}

template <class T> void LinkedList<T>::printList() {
	ListNode<T> *node = start;
	cout << "List: ";
	while (node) {
		cout << *(node->data) << ", ";
		node = node->next;
	}
	cout << endl;
}

#endif