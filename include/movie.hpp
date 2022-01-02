#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "SinglyLinkedList.hpp"
#include "genre.hpp"
#include "actor.hpp"
#include "director.hpp"

struct Movie {
    std::string show_id, type, name, country, date_added, release_year, duration, description, rating;
    //storing in graphs
    LinkedList<Genre<Movie*>*> category;
    LinkedList<Actor<Movie*>*> actors;
    LinkedList<Director<Movie*>*> directors;
    //storing movies
};

#endif