#ifndef TRIES_H
#define TRIES_H

#include<iostream>
#include"avl_tree.hpp"
#include<bits/stdc++.h>
#include"SinglyLinkedList.hpp"

using namespace std;

template <class T>class TrieNode {
public:
    T *data;
    bool isEndOfWord;
    AVL<char, TrieNode<T>*> *children;
    TrieNode(T *data = NULL);
    ~TrieNode();
};

template <class T> class Trie {
public:
    TrieNode<T>* root;
    Trie();
    ~Trie();
    void insert(string, T*);
    T* search(string);
    void remove(string);
private:
    void search(TrieNode<T>*, LinkedList<T*>*);
    void traverse(AVLNode<char, TrieNode<T>*> *curr, LinkedList<T*> *list);
    int (*hash)(char);
};

template <class T>TrieNode<T>::TrieNode(T *data) {
    this->data = data;
    isEndOfWord = false;
    children = new AVL<char, TrieNode<T>*>;
}

template <class T>TrieNode<T>::~TrieNode() {
    delete children;
}

template <class T>Trie<T>::Trie() {
    this->root = new TrieNode<T>();
}

template <class T>Trie<T>::~Trie() {
    delete root;
}

template <class T>void Trie<T>::insert(string key, T *data) {
    TrieNode<T> *current = root;

    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) {
            current->children->insert(key[i], new TrieNode<T>());
        }
        
        current = current->children->search(key[i]);
    }
    current->isEndOfWord = true;
    current->data = data;
}

template <class T> T* Trie<T>::search(string key) {
    TrieNode<T> *current = root;
    for (int i = 0; i < key.length(); i++) {
        if (current->children->search(key[i]) == NULL) return NULL;
        current = current->children->search(key[i]);
    }

    LinkedList<T*> *list = new LinkedList<T*>;
    search(current, list);
    list->printList();

    return current->data;
}

template <class T> void Trie<T>::search(TrieNode<T> *node, LinkedList<T*> *list) {
    if (!node) return;
    if (node->isEndOfWord) list->insert(node->data);
    traverse(node->children->root, list);
}

template <class T> void Trie<T>::traverse(AVLNode<char, TrieNode<T>*> *curr, LinkedList<T*> *list) {
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