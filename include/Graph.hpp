#ifndef GRAPH_H
#define GRAPH_H

#include"trie.hpp"
#include"SinglyLinkedList.hpp"
#include"avl_tree.hpp"
#include"movie.hpp"
#include"genre.hpp"
#include"actor.hpp"
#include"director.hpp"

using namespace std;

class Graph {
public:
    AVL<string, Genre<Movie*>*> category;
    Trie<Movie*> movies;
    Trie<Director<Movie*>*> directors;
    Trie<Actor<Movie*>*> actors; 

    Genre<Movie*>* add_category(string);
    Genre<Movie*>* find_category(string);
    Actor<Movie*>* add_actor(string title);
    Director<Movie*>* add_director(string title);

    void add_movie(Movie* data);
    Movie* search_by_actor(string);
    Movie* search_by_director(string);
    Movie* search_by_title(string);
};

#endif