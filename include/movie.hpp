#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "SinglyLinkedList.hpp"

struct Movie {
    std::string *show_id, *type, *title, *director, *country, *date_added, *release_year, *duration, *description, *rating;
    LinkedList<string*> *cast, *listed_in;
    LinkedList<Movie*> edges;

    Movie() {
        show_id = new std::string(); 
        cast = new LinkedList<string*>;
        listed_in = new LinkedList<string*>;
        type = new std::string(); 
        title = new std::string(); 
        director = new std::string(); 
        country = new std::string(); 
        date_added = new std::string(); 
        release_year = new std::string(); 
        duration = new std::string(); 
        description = new std::string(); 
        rating = new std::string();
    }

    ~Movie() {
        delete show_id;
        delete type;
        delete title;
        delete director;
        delete cast;
        delete country;
        delete date_added;
        delete release_year;
        delete duration;
        delete listed_in;
        delete description;
        delete rating;
    }
};

#endif