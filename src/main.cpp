#include<iostream>
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/movie.hpp"
#include"../include/avl_tree.hpp"

using namespace std;

int main () {
     Trie<Movie> trie;
     LinkedList<Movie*> *movies = get_data();
     int count = 0;

     //populating the tree

     ListNode<Movie*>* curr = movies->start;
     while (curr && curr->data) 
     { 
         trie.insert(curr->data->title, curr->data);
         curr = curr->next;
         count++;
     }

    Movie *test = trie.search("a");

    curr = movies->start;
    ListNode<Movie*> *prev = NULL;
    while(curr) 
    {
        prev = curr;
        curr = curr->next;
        delete prev->data; 
    }

    delete movies;
}



// graph population
// UI