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

// Time Complexity Analysis for add_actor, add_director, search_by_director, search_by_title, search_by_genere is the same since method of traversal is common
// Note: i is a subscript,  m = length of the key (string)
// Best Case: m (each character in the key is root of its tree = each trie linked to one other tri node)
// Average Case = Sigma (from 0 to m) of log (ni), where ni is the number of children in the i-th trie node
// Example: (Store alt)
// Data already stored: ali, all, basit, cat. Time complexity would be: log(3) + log (1) + log (1)  
// Explanation: Root has 3 children (a,b,c) so log(3), a has 1 child (l) so log(1), l has 2 children (l,i) so log(2) to store t 
// Worst Case = O(m)
// each trie linked to 230 (Capital letters not stored) other trie = effectively Constant since Ceil(Log(230)) = 8
// Hence, can be said to be dependent on the length of key 

class Graph {
public:
    AVL<string, Genre<Movie*>*> category; // genre
    Trie<Movie*> movies; // trie of movies
    Trie<Director<Movie*>*> directors; // trie of directors
    Trie<Actor<Movie*>*> actors;  // trie of actors

    ~Graph();
    Genre<Movie*>* add_category(string); // O (Log n) where n = number of category nodes
    Genre<Movie*>* find_category(string); // O (Log n) where n = number of category nodes
    Actor<Movie*>* add_actor(string title);  // mentioned above
    Director<Movie*>* add_director(string title); // mentioned above

    void add_movie(Movie* data); 
    Actor<Movie*>* search_by_actor(string); // O(m + n) where m = length of string, n = nodes in the sub tree of last node (allows recommendation / prefix searching)
    Movie* search_by_director(string); // O(m + n) where m = length of string, n = nodes in the sub tree of last node (allows recommendation / prefix searching)
    Movie* search_by_title(string); // O(m + n) where m = length of string, n = nodes in the sub tree  of last node (allows recommendation / prefix searching)
    Movie* search_by_genre(string title); // O(m + n) where m = length of string, n = nodes in the sub tree  of last node (allows recommendation / prefix searching)
    LinkedList<Movie*>* recommend_movies(string title); // O (n^2)
    void print_directors_by_genre(string title); // O(n*m), where n = number of movies, m = number of directors
};

#endif