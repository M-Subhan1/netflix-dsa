#ifndef GraphACTOR_H
#define GraphACTOR_H

#include"trie.hpp"
#include"SinglyLinkedList.hpp"
#include"avl_tree.hpp"
#include"movie.hpp"
#include "actor.hpp"

using namespace std;

template<class T> class ActorGraph {
public:
    AVL<string, Actor<Movie*>*> cast;
    Trie<T> data;
    
    Actor<Movie*>* add_actor(string);
    Actor<Movie*>* find_actor(string);
    void add_node(T data);
};

template<class T> Actor<Movie*>* ActorGraph<T>::add_actor(string actor) {
    Actor<Movie*>* found = find_actor(actor);
    if (found) return found;

    Actor<Movie*> *ptr = new Actor<Movie*>(actor);

    this->cast.insert(actor, ptr);
    return ptr;
}

template<class T> Actor<Movie*>* ActorGraph<T>::find_actor(string actor) {
    Actor<Movie*> *found = this->cast.search(actor);
    if (found) return found;
    return NULL;
}

template<class T> void ActorGraph<T>::add_node(T data) {
    this->data.insert(data->title, data);
}
#endif