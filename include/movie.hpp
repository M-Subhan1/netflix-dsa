#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "SinglyLinkedList.hpp"

struct Movie {
    std::string *show_id, *type, *title, *director, *country, *date_added, *release_year, *duration, *description, *rating;
    LinkedList<string*> *cast, *listed_in;

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
        if (show_id) delete show_id;
        if (type) delete type;
        if (title) delete title;
        if (director) delete director;
        if (cast) delete cast;
        if (country) delete country;
        if (date_added) delete date_added;
        if (release_year) delete release_year;
        if (duration) delete duration;
        if (listed_in) delete listed_in;
        if (description) delete description;
        if (rating) delete rating;
    }
};

#endif