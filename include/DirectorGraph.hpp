#ifndef DIRECTORGRAPH_H
#define DIRECTORGRAPH_H

#include"trie.hpp"
#include"SinglyLinkedList.hpp"
#include"avl_tree.hpp"
#include"movie.hpp"
#include "director.hpp"

using namespace std;

template <class T> class DirectorGraph {
public:
    AVL<string, Director<Movie*>*> directors;
    Trie<T> data;
    
    Director<Movie*>* add_director(string);
    Director<Movie*>* find_director(string);
    void add_node(T data);
};

template<class T> Director<Movie*>* DirectorGraph<T>::add_director(string director) {
    Director<Movie*>* found = find_director(director);
    if (found) return found;

    Director<Movie*> *ptr = new Director<Movie*>(director);

    this->directors.insert(director, ptr);
    return ptr;
}

template<class T> Director<Movie*>* DirectorGraph<T>::find_director(string director) {
    Director<Movie*> *found = this->directors.search(director);
    if (found) return found;
    return NULL;
}

template<class T> void DirectorGraph<T>::add_node(T data) {
    this->data.insert(data->title, data);
}
#endif