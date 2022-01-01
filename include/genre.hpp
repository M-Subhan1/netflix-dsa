#ifndef GENRE_H
#define GENRE_H

#include<string>
#include"SinglyLinkedList.hpp"

using namespace std;

template <class T> class Genre {
public:
    string name;
    LinkedList<T> list; //list of movies
    Genre(string name) {
        this->name = name;
    }
};

#endif