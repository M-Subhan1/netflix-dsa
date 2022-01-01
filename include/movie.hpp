#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "SinglyLinkedList.hpp"
#include "genre.hpp"
#include "actor.hpp"

struct Movie {
    std::string show_id, type, title, director, country, date_added, release_year, duration, description, rating;
    LinkedList<Genre<Movie*>*> category;

    // LinkedList<string> *cast;
};

#endif