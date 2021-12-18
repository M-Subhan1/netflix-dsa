#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

using namespace std;

template<class K, class D>class HashTable {
D** data;
int(*hash)(K);
const int size;
public:
    HashTable(int, int(*)(K));
    ~HashTable();
    void insert(K, D*);
    void remove(K);
    D* search(K);
};

template <class K, class D> HashTable<K, D>::HashTable(int length, int (*hash)(K)) : size(length) {
    data = new D* [size];
    this->hash = hash;
    for (int i = 0; i < size; i++) data[i] = NULL;
}

template <class K, class D> HashTable<K, D>::~HashTable() {
    for (int i = 0; i < size; i++) delete data[i];
    delete[] data;
}

template <class K, class D> void HashTable<K, D>::insert(K key, D* data) {
    if (search(key) != NULL) return;
    int index = hash(key);
    this->data[index] = data;
}

template <class K, class D> void HashTable<K, D>::remove(K key) {
    int index = hash(key);
    if (this->data[index] == NULL) return;

    D* temp = this->data[index];

    while (temp != NULL) {
        if (temp->key == key) { 
            delete temp;
            return;
        };

        temp = this->data[++index];
    }
}

template <class K, class D> D* HashTable<K, D>::search(K key) {
    int index = hash(key);
    return this->data[index];
}

#endif