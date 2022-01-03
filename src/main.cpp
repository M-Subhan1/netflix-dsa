#include<iostream>
#include"../include/utils.hpp"
#include"../include/Graph.hpp"
#include "../include/SLLQueue.hpp"
#include "../include/director.hpp"

using namespace std;

void displayMenu()
{
    cout << endl;
    cout << " 1. Search movie by title: " << endl;
    cout << " 2. Search movies by genre: " << endl;
    cout << " 3. List movie by actor: " << endl;
    cout << " 4. List movie by director: " << endl;
    cout << " 5. Add to playlist: " << endl;
    cout << " 6. Show my playlist: " << endl;
    cout << " 7. Recommend me something to watch: " << endl;
    cout << " 8. Show co-actors of an actor: " << endl;
    cout << "-1. Exit" << endl;
}

int main () 
{
    Graph *graph = get_graph();
    Playlist<Movie*> p1;

    while(true){
        string userInput;
        int userSelect;
        displayMenu();
        cout << "\nWhat would you like to do? ";
        cin>>userSelect;

        if (userSelect == 1)
        {
            cout << "Enter the name of the movie (auto-completion is enabled): ";
            cin.ignore();
            getline(cin, userInput);
            graph->search_by_title(userInput);
            cout << endl;
            continue;
        }

        else if (userSelect == 2)
        {
            cout << "Enter the name of the genre: ";
            cin.ignore();
            getline(cin, userInput);

            Movie* gen = graph->search_by_genre(userInput);
            if (gen) {
                printMovieDetails(gen);
                cout << endl;
            } else cout << "No matches!" << endl;

            continue;
        }

       else if (userSelect == 3)
        {
            cout << "Enter the name of the actor: ";
            cin.ignore();
            getline(cin, userInput);
            Actor<Movie*> *act = graph->search_by_actor(userInput);

            if (act) {
                act->movie_list.printList(); 
                cout << endl;
            } else cout << "No matches!" << endl;
            continue;
        }

       else if (userSelect == 4)
        {
            cout << "Enter the name of the director: ";
            cin.ignore();
            getline(cin, userInput);
            graph->search_by_director(userInput);
            cout << endl;
            continue;
        }

        else if (userSelect == 5)
        {
            cout << "Enter the name of the movie you would like to put in your playlist: ";
            cin.ignore();
            getline(cin, userInput);

            LinkedList<Movie*> *list = graph->movies.search(userInput);

            if (list) {
                Movie* movie = select_from_list<Movie*>(list);
                p1.enqueue(movie);
            } else {
                cout << "No such movie found!!" << endl;
            }

            cout << endl;

            delete list;
            continue;
        }

        else if (userSelect == 6)
        {
            cout << "Your current playlist: ";
            p1.printList();
            cout << endl;
            continue;
        }

        else if (userSelect == 7)
        {   
            string input;
            cout << "Enter a movie to find similar movies: ";

            cin.ignore();
            getline(cin, input);
            graph->recommend_movies(input);
            continue;
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
               // update printing
                while (curr)
                {
                    curr->data->actors.printList(act->name); // This does not return unique names yet. Add uniqueness in linked list's function directly?
                    curr = curr -> next;
                }
           }

           continue;
        }

        else if (userSelect == -1) {
            break;
        }
    }

    delete graph;
}
