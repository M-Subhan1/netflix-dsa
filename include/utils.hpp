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

template <class T> T select_from_list (LinkedList<T> *list) {
    if (!list || !list->start) return NULL;
    ListNode<T> *curr = list->start;
    int input = -1;
    int index = 0;

    while(true) {
        cout << "Choose an option (-1 to exit): " << endl;
        int list_number = 1;

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
        for (int i = 1; i < (index + input) && i < list->length; i++) curr = curr->next;
        return curr->data;
    }
}

#endif