#ifndef TRIES_H
#define TRIES_H

#include<iostream>
#include"avl_tree.hpp"
#include<bits/stdc++.h>
#include"SinglyLinkedList.hpp"

using namespace std;

template <class T>class TrieNode {
public:
    T data;
    bool isEndOfWord;
    AVL<char, TrieNode<T>*> *children;
    TrieNode();
    ~TrieNode();
};

template <class T> class Trie {
public:
    TrieNode<T>* root;
    Trie();
    ~Trie();
    void insert(string, T);
    LinkedList<T>* search(string);
    void remove(string);
    void destroy(TrieNode<T>*);
    void destroyValues(TrieNode<T>*);
    TrieNode<T>* searchExact(string key);
private:
    void search(TrieNode<T>*, LinkedList<T>*);
    void destroyHelper(AVLNode<char, TrieNode<T>*> *);
    void destroyValuesHelper(AVLNode<char, TrieNode<T>*> *node);
    void traverse(AVLNode<char, TrieNode<T>*> *curr, LinkedList<T> *list);
};

template <class T>TrieNode<T>::TrieNode() {
    isEndOfWord = false;
    children = new AVL<char, TrieNode<T>*>;
}

template <class T>TrieNode<T>::~TrieNode() {
    if (children) delete children;
    children = NULL;
}

template <class T>Trie<T>::Trie() {
    this->root = new TrieNode<T>();
}

template <class T>Trie<T>::~Trie() {
    destroy(root);
}

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
    
    LinkedList<T> *list = new LinkedList<T>;
    search(current, list);
    return list;
}

template <class T> TrieNode<T>* Trie<T>::searchExact(string key) {
    TrieNode<T> *current = root;
    std::for_each(key.begin(), key.end(), [](char & c) {
        c = ::tolower(c);
    }); 

    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) return NULL;
        current = current->children->search(key[i]);
    }
    
    if (current->isEndOfWord) return current;

    return NULL;
}

template <class T> void Trie<T>::search(TrieNode<T> *node, LinkedList<T> *list) {
    if (!node) return;
    if (node->isEndOfWord) list->insert(node->data);
    traverse(node->children->root, list);
}

template <class T> void Trie<T>::destroy(TrieNode<T> *node) {
    if (node) {
        destroyHelper(node->children->root);
        delete node;
    }
}

template <class T> void Trie<T>::destroyHelper(AVLNode<char, TrieNode<T>*> *node) {
    if (node) {
        destroyHelper(node->lchild);
        destroyHelper(node->rchild);
        destroy(node->data);
    }
}

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