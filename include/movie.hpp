#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>

struct Movie {
    std::string *show_id, *type, *title, *director, *cast, *country, *date_added, *release_year, *duration, *listed_in, *description, *rating;

    Movies ** edges;
    
    Movie() {
        show_id = new std::string(); 
        type = new std::string(); 
        title = new std::string(); 
        director = new std::string(); 
        cast = new std::string(); 
        country = new std::string(); 
        date_added = new std::string(); 
        release_year = new std::string(); 
        duration = new std::string(); 
        listed_in = new std::string(); 
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

struct Movies {
    const int size;
    Movie** list;
    Movies(int x): size(x) {
        list = new Movie*[size];
        for (int i = 0; i < size; i++) list[i] = NULL;
    }

    ~Movies() {
        for (int i = 0; i < size; i++) if (list[i]) delete list[i];
        if (list) delete[] list;
    }
};

#endif