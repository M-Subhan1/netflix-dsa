#include<iostream>
#include"../include/utils.hpp"
#include"../include/Graph.hpp"
#include "../include/SLLQueue.hpp"
#include "../include/director.hpp"

using namespace std;

void displayMenu()
{
    cout << "1. Search movie by title: " << endl;
    cout << "2. List movies by genre: " << endl;
    cout << "3. List movie by actor: " << endl;
    cout << "4. List movie by director: " << endl;
    cout << "5. Add to playlist: " << endl;
    cout << "6. Show my playlist: " << endl;
    cout << "7. Recommend me something to watch: " << endl;
    cout << "8. Show co-actors of an actor: " << endl;
}

//main functions
//playlist to find movie and no recommendations just exact movies
//recommendation system

int main () 
{
    LinkedList<Movie*> *movies = new LinkedList<Movie*>; 
    LinkedList<Actor<Movie*>*> *actors = new LinkedList<Actor<Movie*>*> ; 
    LinkedList<Director<Movie*>*> *directors = new LinkedList<Director<Movie*>*>; 
    LinkedList<Genre<Movie*>*> *genre = new LinkedList<Genre<Movie*>*>;

    Graph *graph = get_graph(movies, actors, directors, genre);
   // graph->movies.search("Aziz");
    //graph->actors.search("derek");
    //graph->directors.search("vanessa");

    string userInput;
    Playlist<Movie*> p1;
    cout << "input: ";
    cin >> userInput;
    TrieNode<Movie*> *user = graph->movies.searchExact(userInput);
     if (user) 
     p1.enqueue(user->data);

     p1.printList();
    


    // graph->search_by_director("vanessa");
    // Playlist p1;
    // Trie<Movie*> trie;
    // LinkedList<Movie*> *movies = get_movies();
    // ListNode<Movie*>* curr = movies->start;

    // while (curr && curr->data) //storing movies in the trie
    // { 
    //     trie.insert(curr->data->title, curr->data);
    //     curr = curr->next;
    // }

    // Graph<Movie*> *genres = get_genre(); //populating graph for genres
    // ActorGraph<Movie*>* actors = get_cast(); //populating graph for cast
    // DirectorGraph<Movie*>* directors = get_directors(); //populating graph for directors

    // displayMenu();
    // while(true){
    //     string userInput;
    //     int userSelect;
    //     cout << "What would you like to do: ";
    //     cin>>userSelect;

    //     if (userSelect == 1)
    //     {
    //         cout << "Enter the name of the movie (auto-completion is enabled): ";
    //         cin.ignore();
    //         getline(cin, userInput);
    //         Movie *test = trie.search(userInput);
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    //     if (userSelect == 2)
    //     {
    //         cout << "Enter the name of the genre: ";
    //         cin.ignore();
    //         getline(cin, userInput);
    //         Genre<Movie*>* found = genres->find_category(userInput);
    //         found->list.printList();
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    //     if (userSelect == 3)
    //     {
    //         cout << "Enter the name of the actor: ";
    //         cin.ignore();
    //         getline(cin, userInput);
    //         Actor<Movie*>* found = actors->find_actor(userInput);
    //         found->movie_list.printList();
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    //     if (userSelect == 4)
    //     {
    //         cout << "Enter the name of the director: ";
    //         cin.ignore();
    //         getline(cin, userInput);
    //         Director<Movie*>* found = directors->find_director(userInput);
    //         found->movie_list.printList();
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    //     if (userSelect == 5)
    //     {
    //         cout << "Enter the name of the movie you would like to put in your playlist: ";
    //         cin.ignore();
    //         getline(cin, userInput);

    //         Movie * user = trie.search(userInput);
    //         if (user) p1.playlist.Enqueue(user);
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    //     if (userSelect == 6)
    //     {
    //         cout << "Your current playlist: ";
    //         p1.show_playlist();
    //         cout << endl;
    //         displayMenu();
    //         continue;
    //     }

    // }





    // ActorGraph<Movie*>* actors = get_cast();
    // Actor<Movie*>* found = actors->find_actor("Vanessa Hudgens");
    // found->movie_list.printList();

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

    // while (curr && curr->data) 
    // { 
    //     trie.insert(curr->data->title, curr->data);
    //     curr = curr->next;
    //     count++;
    // }

    // Movie *test = trie.search("a");

    ListNode<Movie*>* curr = movies->start;
    ListNode<Movie*> *prev = NULL;
    while(curr) 
    {
        prev = curr;
        curr = curr->next;
        if (prev->data) delete prev->data; 
    }

    delete movies;

    ListNode<Actor<Movie*>*> *temp = actors->start;
    ListNode<Actor<Movie*>*> *temp2 = actors->start;
    temp2 = NULL;
    while(temp) 
    {
        temp2 = temp;
        temp = temp->next;
        if (temp2->data) delete temp2->data; 
    }

    delete actors;


    ListNode<Director<Movie*>*> *pd = directors->start;
    ListNode<Director<Movie*>*> *d = directors->start;
    pd = NULL;
    while(d) 
    {
        pd = d;
        d = d->next;
        if (pd->data) delete pd->data; 
    }

    delete directors;


    
    ListNode<Genre<Movie*>*> *g = genre->start;
    ListNode<Genre<Movie*>*> *pg = NULL;
    while(g) 
    {
        pg = g;
        g = g->next;
        if (pg->data) delete pg->data; 
    }

    delete genre;

    delete graph;
}



// graph population