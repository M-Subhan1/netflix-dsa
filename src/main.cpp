#include<iostream>
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/movie.hpp"
#include"../include/avl_tree.hpp"

using namespace std;

int main () {
    Trie<Movie> trie;
    LinkedList<Movie*> *movies = get_data("../data/netflix_titles.csv");

    // populating the tree
    ListNode<Movie*>* curr = movies->start;
    while (curr && curr->data) 
    { 
        trie.insert(*(curr->data->title), curr->data);
        curr = curr->next;
    }

    Movie *test = trie.search("Aziza");
    cout << test << endl;
}

// graph population
// UI