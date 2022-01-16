#ifndef UTILS_H
#define UTILS_H

#include"movie.hpp"
#include"Graph.hpp"
#include"genre.hpp"
#include"actor.hpp"
#include "../include/director.hpp"

Graph* get_graph(); // populate and retrieve graph
void parse_genre(string genre, Movie*, Graph *); // parse genre and link with movies
void parse_actor(string cast, Movie*, Graph *); // parse actors and link with movies
void parse_directors(string director, Movie*, Graph *); // parse directors and link with movies

template <class T> T select_from_list (LinkedList<T> *list) { // reusable UI to select from a list
    if (!list || !list->start) return NULL;
    ListNode<T> *curr = list->start;
    int input = -1;
    int index = 1;

    while(true) {
        cout << "Choose an option (-1 to exit, 0 to view more): " << endl;
        int list_number = 0;

        while (list_number < 10 && curr)
        {
            cout << index + list_number << ". " << curr->data->name << endl;
            curr = curr->next;
            list_number++;
        }
        
        cout << "? ";
        cin >> input;

        if (input == -1) return NULL;
        else if (input == 0) {
            index = list_number + index;
            continue;
        }
        else if (input < 1 || input >= (index + list_number) ) {
            curr = list->start;
            cout << "Please select a valid option!" << endl;
            continue; 
        }

        cout << input << endl;

        curr = list->start;
        for (int i = 1; i < input && i < list->length; i++) curr = curr->next;
        
        return curr->data;
    }
}
void printMovieDetails(Movie* movie); // prints a movie

#endif