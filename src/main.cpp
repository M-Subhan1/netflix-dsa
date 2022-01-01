#include<iostream>
#include"../include/utils.hpp"
#include"../include/Graph.hpp"

using namespace std;

int main () {
    Graph<Movie*> *movies = get_data();

    Movie* search = movies->data.search("MAtrix");
    LinkedList<Genre<Movie*>*> *genre = &search->category; 

    ListNode<Genre<Movie*>*> *node = genre->start;
    ListNode<Movie*> *temp2;

    // while(node) {
        if (node && node->data) {
            cout << node->data->name << endl;
            node->data->list.printList();
            cout << node->data->name << endl;
        }
        // while (temp2)
        // {
        //     cout << temp2->data << endl;
        //     temp2 = temp2->next;
        // }
        // node = node->next;
    // }

    delete movies;
    // Trie<Movie*> trie;
    // int count = 0;

    //  //populating the tree

    // ListNode<Movie*>* curr = movies->start;
    // while (curr && curr->data) 
    // { 
    //     trie.insert(curr->data->title, curr->data);
    //     curr = curr->next;
    //     count++;
    // }

    // Movie *test = trie.search("a");

    // curr = movies->start;
    // ListNode<Movie*> *prev = NULL;
    // while(curr) 
    // {
    //     prev = curr;
    //     curr = curr->next;
    //     delete prev->data; 
    // }

    // delete movies;
}



// graph population
// UI