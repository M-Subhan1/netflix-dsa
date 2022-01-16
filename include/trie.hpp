#ifndef TRIES_H
#define TRIES_H

#include<iostream>
#include"avl_tree.hpp"
#include<bits/stdc++.h>
#include"SinglyLinkedList.hpp"

using namespace std;

// Trie node to store data type T
template <class T>class TrieNode {
public:
    T data;
    bool isEndOfWord;
    AVL<char, TrieNode<T>*> *children;
    TrieNode();
    ~TrieNode();
};

// Trie to store data T
template <class T> class Trie {
public:
    TrieNode<T>* root; // root of the trie
    Trie(); // constructor
    ~Trie(); // destrcutor
    void insert(string, T); // insert data against string provided
    LinkedList<T>* search(string); // overloaded search (with auto complete/ suggestions)
    void remove(string); // remove a node against string
    void destroy(TrieNode<T>*); // destroy the trie from a given root
    void destroyValues(TrieNode<T>*); // deletes values stored in trie nodes (be careful using this)
    TrieNode<T>* searchExact(string key); // search for an exact match
private:
    void search(TrieNode<T>*, LinkedList<T>*); // main osearch with autocomplete
    void destroyHelper(AVLNode<char, TrieNode<T>*> *); // ehlper to destroy tree
    void destroyValuesHelper(AVLNode<char, TrieNode<T>*> *node); // helper to destroy values
    void traverse(AVLNode<char, TrieNode<T>*> *curr, LinkedList<T> *list); // traverse the Trie
};

// constructor Trie Node
template <class T>TrieNode<T>::TrieNode() {
    isEndOfWord = false;
    children = new AVL<char, TrieNode<T>*>;
}

// destrcutor Trie Node
template <class T>TrieNode<T>::~TrieNode() {
    if (children) delete children;
    children = NULL;
}

// constructor Trie
template <class T>Trie<T>::Trie() {
    this->root = new TrieNode<T>();
}

// destrcutor Trie
template <class T>Trie<T>::~Trie() {
    destroy(root);
}

// Time Complexity Analysis for Insert, Search Exact, Delete Functions is the same since method of traversal is common
// Insertion, deletion of data always takes Log (n) where n is the number of nodes in the AVL tree we are inserting in
// Note: i is a subscript,  m = length of the key (string)
// Best Case: m (each character in the key is root of its tree)
// Worst Case & Average Cases = Sigma (from 0 to m) of log (ni), where ni is the number of children in the i-th trie node
// Example: (Store alt)
// Data already stored: ali, all, basit, cat. Time complexity would be: log(3) + log (1) + log (1)  
// Explanation: Root has 3 children (a,b,c) so log(3), a has 1 child so log(1), l has 2 children so log(2) to store t 
// If we assume that each tree has an evenly distributed nodes (n nodes in each child avl tree)
// We can then say that Time Complexity = m Log (n), in real world scenarios this isnt possible so the time complexity would be the sum at each node

template <class T>void Trie<T>::insert(string key, T data) {
    TrieNode<T> *current = root;
    std::for_each(key.begin(), key.end(), [](char & c) {
        c = ::tolower(c);
    }); 

    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) {
            current->children->insert(key[i], new TrieNode<T>);
        }
        
        current = current->children->search(key[i]);
    }
    current->isEndOfWord = true;
    current->data = data;
}

template <class T> LinkedList<T>* Trie<T>::search(string key) {
    TrieNode<T> *current = root;
    std::for_each(key.begin(), key.end(), [](char & c) {
        c = ::tolower(c);
    }); 

    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) return NULL;
        current = current->children->search(key[i]);
    }
    
    LinkedList<T> *list = new LinkedList<T>; // create list
    search(current, list); // pass list as container
    return list;
}

template <class T> TrieNode<T>* Trie<T>::searchExact(string key) {
    TrieNode<T> *current = root;

    // convert string to lower case (makes searching case insensitive)
    std::for_each(key.begin(), key.end(), [](char & c) {
        c = ::tolower(c);
    }); 

    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) return NULL;
        current = current->children->search(key[i]);
    }
    
    if (current->isEndOfWord) return current; // return exact match
    // else return null
    return NULL;
}

// takes a trie node and a list
template <class T> void Trie<T>::search(TrieNode<T> *node, LinkedList<T> *list) {
    if (!node) return;
    if (node->isEndOfWord) list->insert(node->data);
    traverse(node->children->root, list); // calling traverse on children of the trie node (avl tree)
}

//
template <class T> void Trie<T>::destroy(TrieNode<T> *node) {
    if (node) {
        destroyHelper(node->children->root);
        delete node;
    }
}

// traverse entrie trie and deletes nodes
template <class T> void Trie<T>::destroyHelper(AVLNode<char, TrieNode<T>*> *node) {
    if (node) {
        destroyHelper(node->lchild);
        destroyHelper(node->rchild);
        destroy(node->data);
    }
}

// traverses entire trie  and delete values (data stored in trie node), recursively calls
template <class T> void Trie<T>::destroyValues(TrieNode<T> *node) {
    if (node) {
        destroyValuesHelper(node->children->root);
        if (node->isEndOfWord) {
            delete node->data;
            node->isEndOfWord = false;
        }
    }
}

template <class T> void Trie<T>::destroyValuesHelper(AVLNode<char, TrieNode<T>*> *node) {
    if (node) {
        destroyValuesHelper(node->lchild);
        destroyValuesHelper(node->rchild);
        destroyValues(node->data);
    }
}

template <class T> void Trie<T>::traverse(AVLNode<char, TrieNode<T>*> *curr, LinkedList<T> *list) {
    if (curr) {
        // traverse left, right and then print
        traverse(curr->lchild, list);
        search(curr->data, list);
        traverse(curr->rchild, list);
    }
}

template <class T>void Trie<T>::remove(string key) {
    TrieNode<T> *current = root;
    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) return;
        current = current->children->search(key[i]);
    }

    current->isEndOfWord = false;
    current->data = NULL;
}

#endif