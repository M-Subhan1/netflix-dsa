#ifndef SLLQ_H
#define SLLQ_H
#include <iostream>
using namespace std;

template <class T> class ListNode {
public:
	T data;
	ListNode *next;
	ListNode(T val);
};

template <class T> class Playlist {
public:
	Playlist();
	~Playlist();
	ListNode<T> *start; // special variable which stores address of the head node.
	ListNode<T> *last; // special variable which stores address of the last node.
	ListNode<T> *pLoc; // to be used by Search(value) method to store address
	ListNode<T> *loc; // to be used by Search(value) method to store 
	void printList();
    void dequeue(T); 
	void enqueue(T);
};

template <class T> ListNode<T>::ListNode(T val) {
	// Initializing ListNode
	data = val;
	next = NULL;
}

template <class T> Playlist<T>::Playlist() {
	// Init Linked List
	start = last = pLoc = loc = NULL;
}

template <class T> Playlist<T>::~Playlist() {
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

template <class T> void Playlist<T>::printList() {
	ListNode<T> *node = start;
	cout << "List: ";
	while (node) {
		cout << *(node->data) << ", ";
		node = node->next;
	}
	cout << endl;
}

template <class T> void Playlist<T>::dequeue(T value) // takes input from a user and inserts it at the front of a list
{
	ListNode<T>* temp = start;

	if (start != NULL) //list is not empty
	{
		temp = temp->next;
        delete start;
		start = new_node;
	}

	else //updating last pointer if list is empty
	cout << "Playlist empty." << endl;
}

template <class T> void Playlist<T>::enqueue(T value) //inserts value at end of a list
{
	ListNode<T>* new_node = new ListNode<T>();	//creating a new node

	new_node->data = value;	//storing value in the node

	if (!IsEmpty())
	{
		new_node->next = NULL;
		last->next = new_node;
		last = new_node;
	}

	else   //updating last and start pointer if list is empty
	{
		start = new_node;
		last = new_node;
		new_node->next = NULL;
	}
}

#endif