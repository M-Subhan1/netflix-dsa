#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "SinglyLinkedList.hpp"

struct Movie {
    std::string show_id, type, title, director, country, date_added, release_year, duration, description, rating;
    LinkedList<string> *cast, *listed_in;

    Movie() {
        cast = new LinkedList<string>;
        listed_in = new LinkedList<string>;
    }

    ~Movie() {
        if (cast) delete cast;
        if (listed_in) delete listed_in;
    }
};

#endif