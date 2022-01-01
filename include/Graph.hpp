#ifndef GRAPH_H
#define GRAPH_H

#include"trie.hpp"
#include"SinglyLinkedList.hpp"
#include"avl_tree.hpp"
#include"movie.hpp"

using namespace std;

template<class T> class Graph {
public:
    AVL<string, Genre<Movie*>*> category;
    Trie<T> data;
    Genre<Movie*>* add_category(string);
    Genre<Movie*>* find_category(string);
    void add_node(T data);
};

template<class T> Genre<Movie*>* Graph<T>::add_category(string category) {
    Genre<Movie*>* found = find_category(category);
    if (found) return found;

    Genre<Movie*> *ptr = new Genre<Movie*>(category);

    this->category.insert(category, ptr);
    return ptr;
}

template<class T> Genre<Movie*>* Graph<T>::find_category(string category) {
    Genre<Movie*> *found = this->category.search(category);
    if (found) return found;
    return NULL;
}

template<class T> void Graph<T>::add_node(T data) {
    this->data.insert(data->title, data);
}

#endif