#include<iostream>
#include"../include/utils.hpp"
#include"../include/Graph.hpp"
#include "../include/SLLQueue.hpp"
#include "../include/director.hpp"

using namespace std;

void displayMenu()
{
    cout << "1. Search movie by title: " << endl;
    cout << "2. Search movies by genre: " << endl;
    cout << "3. List movie by actor: " << endl;
    cout << "4. List movie by director: " << endl;
    cout << "5. Add to playlist: " << endl;
    cout << "6. Show my playlist: " << endl;
    cout << "7. Recommend me something to watch: " << endl;
    cout << "8. Show co-actors of an actor: " << endl;
}

//recommendation system

int main () 
{
    LinkedList<Movie*> *movies = new LinkedList<Movie*>; 
    LinkedList<Actor<Movie*>*> *actors = new LinkedList<Actor<Movie*>*> ; 
    LinkedList<Director<Movie*>*> *directors = new LinkedList<Director<Movie*>*>; 
    LinkedList<Genre<Movie*>*> *genre = new LinkedList<Genre<Movie*>*>;
    Graph *graph = get_graph(movies, actors, directors, genre);
    Playlist<string> p1;

     displayMenu();
    while(true){
        string userInput;
        int userSelect;
        cout << "What would you like to do: ";
        cin>>userSelect;

        if (userSelect == 1)
        {
            cout << "Enter the name of the movie (auto-completion is enabled): ";
            cin.ignore();
            getline(cin, userInput);
            graph->search_by_title(userInput);
            cout << endl;
            displayMenu();
            continue;
        }

        else if (userSelect == 2)
        {
            cout << "Enter the name of the genre: ";
            cin.ignore();
            getline(cin, userInput);
            Movie* gen = graph->search_by_genre(userInput);
            cout << gen->name;
            cout << endl;
            displayMenu();
            continue;
        }

       else if (userSelect == 3)
        {
            cout << "Enter the name of the actor: ";
            cin.ignore();
            getline(cin, userInput);
           Actor<Movie*> *act = graph->search_by_actor(userInput);
           act->movie_list.printList(); 
            cout << endl;
            displayMenu();
            continue;
        }

       else if (userSelect == 4)
        {
            cout << "Enter the name of the director: ";
            cin.ignore();
            getline(cin, userInput);
            graph->search_by_director(userInput);
            cout << endl;
            displayMenu();
            continue;
        }

        else if (userSelect == 5)
        {
            cout << "Enter the name of the movie you would like to put in your playlist: ";
            cin.ignore();
            getline(cin, userInput);

            p1.enqueue(userInput);
            cout << endl;
            displayMenu();
            continue;
        }

        else if (userSelect == 6)
        {
            cout << "Your current playlist: ";
            p1.printList();
            cout << endl;
            displayMenu();
            continue;
        }

        else if (userSelect == 7)
        {
            // recommendation comes here
        }

        else if (userSelect == 8)
        {
           cout << "Enter the name of the actor to find their co-actors: ";
           cin.ignore();
           getline(cin, userInput);
           Actor<Movie*> *act = graph->search_by_actor(userInput);
           LinkedList<Movie*> *movieListofActor = &act->movie_list;
           ListNode<Movie*> *curr = movieListofActor->start;
           if(curr)
           {
                while (curr)
                {
                    curr->data->actors.printList(); // This does not return unique names yet. Add uniqueness in linked list's function directly?
                    curr = curr -> next;
                }
           }

           displayMenu();
           continue;
        }
    }

    // ListNode<Movie*>* curr = movies->start;
    // ListNode<Movie*> *prev = NULL;
    // while(curr) 
    // {
    //     prev = curr;
    //     curr = curr->next;
    //     if (prev->data) delete prev->data; 
    // }

    // delete movies;

    // ListNode<Actor<Movie*>*> *temp = actors->start;
    // ListNode<Actor<Movie*>*> *temp2 = actors->start;
    // temp2 = NULL;
    // while(temp) 
    // {
    //     temp2 = temp;
    //     temp = temp->next;
    //     if (temp2->data) delete temp2->data; 
    // }

    // delete actors;


    // ListNode<Director<Movie*>*> *pd = directors->start;
    // ListNode<Director<Movie*>*> *d = directors->start;
    // pd = NULL;
    // while(d) 
    // {
    //     pd = d;
    //     d = d->next;
    //     if (pd->data) delete pd->data; 
    // }

    // delete directors;


    
    // ListNode<Genre<Movie*>*> *g = genre->start;
    // ListNode<Genre<Movie*>*> *pg = NULL;
    // while(g) 
    // {
    //     pg = g;
    //     g = g->next;
    //     if (pg->data) delete pg->data; 
    // }

    // delete genre;

    // delete graph;
}
