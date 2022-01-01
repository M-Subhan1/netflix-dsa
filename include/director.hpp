#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "SinglyLinkedList.hpp"
#include "movie.hpp"
#include <iostream>
using namespace std;

template <class T> class Director {
public:
    std::string name;
    LinkedList<T> movie_list;

    Director(string name) {
        this->name = name;
    }
};


#endif