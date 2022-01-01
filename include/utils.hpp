#ifndef UTILS_H
#define UTILS_H

#include"movie.hpp"
#include"Graph.hpp"
#include"genre.hpp"
#include"actor.hpp"

Graph<Movie*> *get_data ();
void parse_genre(string genre, Movie*, Graph<Movie*> *); 
void parse_actor(string cast, Movie*, Graph<Actor*> *);

#endif