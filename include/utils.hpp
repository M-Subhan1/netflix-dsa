#ifndef UTILS_H
#define UTILS_H

#include"movie.hpp"
#include"Graph.hpp"
#include"genre.hpp"
#include"actor.hpp"
#include "../include/director.hpp"

Graph* get_graph(LinkedList<Movie*> *, LinkedList<Actor<Movie*>*> *, LinkedList<Director<Movie*>*> *, LinkedList<Genre<Movie*>*> *genre);
void parse_genre(string genre, Movie*, Graph *, LinkedList<Genre<Movie*>*> *); 
void parse_actor(string cast, Movie*, Graph *, LinkedList<Actor<Movie*>*> *);
void parse_directors(string director, Movie*, Graph *, LinkedList<Director<Movie*>*> *);

#endif