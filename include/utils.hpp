#ifndef UTILS_H
#define UTILS_H

#include"movie.hpp"
#include"Graph.hpp"
#include"genre.hpp"
#include"actor.hpp"
#include "Graph(Actor).hpp"

Graph<Movie*> *get_genre ();
ActorGraph<Movie*> *get_cast ();
LinkedList<Movie*>* get_movies();
LinkedList<std::string>* parse_multivalued_attr(string);
void parse_genre(string genre, Movie*, Graph<Movie*> *); 
void parse_actor(string cast, Movie*, ActorGraph<Movie*> *);

#endif