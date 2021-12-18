#include<iostream>
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/movie.hpp"
#include"../include/avl_tree.hpp"

using namespace std;

int main () {
    Trie<Movie> trie;
    Movies *movies = get_data("../data/netflix_titles.csv");

    // populating a trie
    for (int i = 0; i < movies->size; i++)
        trie.insert(*(movies->list[i]->title), movies->list[i]);


    Movie *test = trie.search("Expedition China");
    if (test) {
        cout << *test->title << endl;
    }
}

// update trie search method