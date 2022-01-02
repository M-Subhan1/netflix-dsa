#ifndef SLLQ_H
#define SLLQ_H
#include <iostream>
using namespace std;

template <class T> class PlaylistNode {
public:
	T data;
	PlaylistNode<T> *next;
	PlaylistNode<T> (T val);
};

template <class T> class Playlist {
public:
	Playlist();
	~Playlist();
	PlaylistNode<T> *start; // special variable which stores address of the head node.
	PlaylistNode<T> *last; // special variable which stores address of the last node.
	PlaylistNode<T> *pLoc; // to be used by Search(value) method to store address
	PlaylistNode<T> *loc; // to be used by Search(value) method to store 
	void printList();
    void dequeue(); 
	void enqueue(T);
};

template <class T> PlaylistNode<T>::PlaylistNode(T val) {
	// Initializing PlaylistNode
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
	PlaylistNode<T> *tempNode = start;
	// iterating over the entire list and deleting nodes
	while (tempNode) {
		pLoc = tempNode;
		tempNode = tempNode->next;
		delete pLoc;
	}
	start = last = NULL;
}

template <class T> void Playlist<T>::printList() {
	PlaylistNode<T> *node = start;
	cout << "List: ";
	while (node) {
		cout << node->data << ", ";
		node = node->next;
	}
	cout << endl;
}

template <class T> void Playlist<T>::dequeue() // takes input from a user and inserts it at the front of a list
{
	PlaylistNode<T>* temp = start;

	if (start != NULL) //list is not empty
	{
		temp = temp->next;
        delete start;
		start = temp;
	}
	else cout << "Playlist empty." << endl;
}

template <class T> void Playlist<T>::enqueue(T value) //inserts value at end of a list
{
	PlaylistNode<T>* new_node = new PlaylistNode<T>(value);	//creating a new node

	//updating last and start pointer if list is empty
	if (start) last->next = new_node;
	else  start = new_node;

	last = new_node;
}

#endif