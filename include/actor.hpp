#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include "SinglyLinkedList.hpp"
#include "movie.hpp"

template <class T> class Actor {
public:
    std::string name;
    LinkedList<T> movie_list;

    Actor(string name) {
        this->name = name;
    }
};

#endif