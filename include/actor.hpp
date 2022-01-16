#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include "SinglyLinkedList.hpp"
#include "movie.hpp"

// class Actor;
template <class T> class Actor {
public:
    std::string name; // actor name
    LinkedList<T> movie_list; // list of movies acted in

    // constructor
    Actor(string name) {
        this->name = name;
    }
};

#endif