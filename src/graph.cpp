#include"../include/Graph.hpp"
#include"../include/utils.hpp"
#include"../include/heap.hpp"

Graph::~Graph() {
    movies.destroyValues(movies.root);
    actors.destroyValues(actors.root);
    directors.destroyValues(directors.root);
    category.destroyValues(category.root);
}

// Time Complexirt : Log(n) where n is the number of category nodes
Genre<Movie*>* Graph::add_category(string category) {
    // search for category, if found return found CATEGORY else add new
    Genre<Movie*>* found = find_category(category); 
    if (found) return found;

    Genre<Movie*> *ptr = new Genre<Movie*>(category); 

    this->category.insert(category, ptr);
    return ptr;
}

// Time Complexirt : Log(n) where n is the number of category nodes
Genre<Movie*>* Graph::find_category(string category) {
    // search for a ctaegory in avl tree, return if found else null
    Genre<Movie*> *found = this->category.search(category);
    if (found) return found;
    return NULL;
}

// Time Complexity : m Logn
void Graph::add_movie(Movie *movie) {
    this->movies.insert(movie->name, movie); // insert into movies trie
}

Actor<Movie*> *Graph::add_actor(string title) {
    // search for an actor, if exists return pointer else insert
    TrieNode<Actor<Movie*>*> *node = this->actors.searchExact(title);

    if (!node || !node->data) { 
        Actor<Movie*> *actor = new Actor<Movie*>(title);
        this->actors.insert(actor->name, actor);
        return actor;
    }
    
    return node->data;
}

Director<Movie*> *Graph::add_director(string title) {
    // search for an actor, if exists return pointer else insert
    TrieNode<Director<Movie*>*> *node = this->directors.searchExact(title);

    if (!node || !node->data) { 
        Director<Movie*> *director = new Director<Movie*>(title);
        this->directors.insert(director->name, director);
        return director;
    }

    return node->data;
}

Movie* Graph::search_by_director(string name) {
    // search for an director, if exists get list of movies directed and use select list function to search
    LinkedList<Director<Movie*>*> *list = directors.search(name);
    
    Director<Movie*> *director = select_from_list<Director<Movie*>*>(list);

    if (director) director->movie_list.printList();
    else cout << "No matches!!" <<endl;

    if (list) delete list;
    return NULL;
}

Actor<Movie*>* Graph::search_by_actor(string name) {
    // search for an director, if exists get list of movies directed and use select list function to search
    LinkedList<Actor<Movie*>*> *list = actors.search(name);
    Actor<Movie*> *actor = select_from_list<Actor<Movie*>*>(list);
    
    if (list) delete list;
    if (actor) return actor;
    else cout << "No matches!!" <<endl;

    return NULL;
}

Movie* Graph::search_by_title(string title) {
    // search for a movie, if exists get list of movies directed and use select list function to search
    // print details of the selected movie
    LinkedList<Movie*> *list = movies.search(title);

    Movie *movie = select_from_list<Movie*>(list);
    if (movie) {
        printMovieDetails(movie);
    } else cout << "No matches!!" << endl;

    if (list) delete list;

    return NULL;
}

Movie* Graph::search_by_genre(string title) {
    Genre<Movie*> *genre = category.search(title); // search for a genre

    if (!genre) return NULL;
    else { // if exists, select a movie using select from list helper
        Movie *movie = select_from_list<Movie*>(&genre->list); 
        return movie;
    }
}

void Graph::print_directors_by_genre(string title) {
    Genre<Movie*> *genre = category.search(title); // search for the genre
    // if exists, print directors of all the movies in the genre

    if (!genre) {
        cout << "No matches!" << endl;
    } else {
        auto node = genre->list.start;
        while (node)
        {   
            node->data->directors.printList();
            node = node->next;
        }
    }
}

// Time Complexity: O(n^2)
// Since it Traverses Every node in Heap as well
LinkedList<Movie*>* Graph::recommend_movies(string title) {
    // search for the movie
    LinkedList<Movie*> *mov = movies.search(title);

    Movie *node = select_from_list<Movie*>(mov); // select movie (allows autocomplete)
    delete mov;

    if (node) { 
        // use selected movie to get all similar movies
        int count = 0, index;
        auto genre = node->category.start;
        LinkedList<Movie*> *list = new LinkedList<Movie*>;
        
        while (genre)
        {
            count += genre->data->list.length;
            genre = genre->next;
        }

        // priority heap
        MaxHeap<Movie*> *heap = new MaxHeap<Movie*>(count); 

        genre = node->category.start;

        while (genre)
        {   
            auto movie = genre->data->list.start;
            // traverse every movie in all related genre for the selected movie node (select above)
            while(movie) {
                if (title.compare(movie->data->name.data()) != 0) {
                    int index = heap->find_value(movie->data); 

                    if (index == -1) { // insert movie in the heap
                        heap->insert(1, movie->data);
                    } else { // if movie already exists, update priority 
                        heap->update_priority(index, heap->data[index]->priority + 1);
                    }
                }
                movie = movie->next;
            }
            genre = genre->next;
        }

        // dequeue 5 movies from the heap and recommend
        for (int i = 0; i < 5; i++) {
            auto temp = heap->pop();
            list->insert(temp->data);
            delete temp;
        }

        cout << "Similar movies: ";
        list->printList(); // print list of similar movies
        
        delete heap;
        delete list;
    }

    return NULL;
}

