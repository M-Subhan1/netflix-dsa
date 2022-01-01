#include<iostream>
#include"../include/utils.hpp"
#include"../include/Graph.hpp"
#include "../include/Graph(Actor).hpp"

using namespace std;

void display_menu(){
    cout<<"1. Search by movie title\n2.Search by genre\n3.Search by actor\n4.Search co-actors of an actor\n5.Add to playlist\n6.Show playlist\n7.Search by director\n8.Show recommendations"<<endl;
}

void search_by_title(string userInput, LinkedList<Movie*>* movies, Trie<Movie*> trie)
{
     Movie *test = trie.search(userInput);
}

void search_by_genre(string userInput,Graph<Movie*>* genres)
{
    Genre<Movie*>* found = genres->find_category(userInput);
    found->list.printList();
}

void insertMovies(Trie<Movie*> trie, LinkedList<Movie*> *movies)
{
    ListNode<Movie*>* curr = movies->start;
    while (curr && curr->data) 
    { 
        trie.insert(curr->data->title, curr->data);
        curr = curr->next;
    }
}


int main () {

    ActorGraph<Movie*>* actors = get_cast();
    Actor<Movie*>* found = actors->find_actor("Vanessa Hudgens");
    found->movie_list.printList();

    // Trie<Movie*> trie;
    // LinkedList<Movie*> *movies = get_movies();
    // ListNode<Movie*>* curr = movies->start;
    // while (curr && curr->data) 
    // { 
    //     trie.insert(curr->data->title, curr->data);
    //     curr = curr->next;
    // }

    // search_by_title("Aziza", movies, trie);
    // Graph<Movie*> *movies = get_genre();
    // // Genre<Movie*>* found = movies->find_category("Independent Movies");
    // // found->list.printList();
    // search_by_genre("Comedy", movies);

    
    //  Movie* search = movies->data.search("Aziza"); //searching movie in trie
    //  LinkedList<Genre<Movie*>*> *genre = &search->category; //creates list pointer of genres pointers for that movie

    //  ListNode<Genre<Movie*>*> *node = genre->start; //iteraring through the list of genres
    //  ListNode<Movie*> *temp2;

    //  while(node) //until list of genres doesnt end continue the loop
    // {
    //      if (node && node->data) {
    //         cout << node->data->name << endl; //name of movie
    //         node->data->list.printList(); //printing list of genres
    //         cout << node->data->name << endl;
    //     }
    //     while (temp2)  //prints all information of the movie
    //     {
    //         cout << temp2->data << endl;
    //         temp2 = temp2->next;
    //     }
    // node = node->next;
    //  }

    // delete movies;
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

    // // // curr = movies->start;
    // // // ListNode<Movie*> *prev = NULL;
    // // // while(curr) 
    // // // {
    // // //     prev = curr;
    // // //     curr = curr->next;
    // // //     delete prev->data; 
    // // // }

    // // // delete movies;


}



// graph population
// UI