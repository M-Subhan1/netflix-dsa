#ifndef TRIES_H
#define TRIES_H

#include<iostream>
#include"avl_tree.hpp"
#include<bits/stdc++.h>

using namespace std;

#define SIZE_ALPHABET 256

template <class T>class TrieNode {
public:
    T *data;
    bool isEndOfWord;
    AVL<TrieNode<T>*> *children;
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
    int (*hash)(char);
};

template <class T>TrieNode<T>::TrieNode(T *data) {
    this->data = data;
    isEndOfWord = false;
    children = new AVL<TrieNode<T>*>;
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
    
    return current->data;
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