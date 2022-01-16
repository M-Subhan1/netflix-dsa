#ifndef GENRE_H
#define GENRE_H

#include<string>
#include"SinglyLinkedList.hpp"

using namespace std;

template <class T> class Genre {
public:
    string name; // name
    LinkedList<T> list; //list of movies in the genre
    Genre(string name) {
        this->name = name;
    }
};

#endif