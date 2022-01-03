#include"../include/Graph.hpp"
#include"../include/utils.hpp"
#include"../include/heap.hpp"

Graph::~Graph() {
    movies.destroyValues(movies.root);
    actors.destroyValues(actors.root);
    directors.destroyValues(directors.root);
    category.destroyValues(category.root);
}

Genre<Movie*>* Graph::add_category(string category) {
    Genre<Movie*>* found = find_category(category);
    if (found) return found;

    Genre<Movie*> *ptr = new Genre<Movie*>(category);

    this->category.insert(category, ptr);
    return ptr;
}

Genre<Movie*>* Graph::find_category(string category) {
    Genre<Movie*> *found = this->category.search(category);
    if (found) return found;
    return NULL;
}

void Graph::add_movie(Movie *movie) {
    this->movies.insert(movie->name, movie);
}

Actor<Movie*> *Graph::add_actor(string title) {
    TrieNode<Actor<Movie*>*> *node = this->actors.searchExact(title);

    if (!node || !node->data) { 
        Actor<Movie*> *actor = new Actor<Movie*>(title);
        this->actors.insert(actor->name, actor);
        return actor;
    }
    
    return node->data;
}

Director<Movie*> *Graph::add_director(string title) {
    TrieNode<Director<Movie*>*> *node = this->directors.searchExact(title);

    if (!node || !node->data) { 
        Director<Movie*> *director = new Director<Movie*>(title);
        this->directors.insert(director->name, director);
        return director;
    }

    return node->data;
}

Movie* Graph::search_by_director(string name) {
    LinkedList<Director<Movie*>*> *list = directors.search(name);
    list->printList();
    Director<Movie*> *director = select_from_list<Director<Movie*>*>(list);
    delete list;

    if (director) {
        director->movie_list.printList();
    }
    return NULL;
}

Actor<Movie*>* Graph::search_by_actor(string name) {
    LinkedList<Actor<Movie*>*> *list = actors.search(name);
    Actor<Movie*> *actor = select_from_list<Actor<Movie*>*>(list);
    delete list;
    if (actor) return actor;
    return NULL;
}

Movie* Graph::search_by_title(string title) {
    LinkedList<Movie*> *list = movies.search(title);

    Movie *movie = select_from_list<Movie*>(list);
    if (movie) {
        printMovieDetails(movie);
    } else cout << "No matches!!" << endl;
    delete list;
    return NULL;
}

Movie* Graph::search_by_genre(string title) {
    Genre<Movie*> *genre = category.search(title);

    if (!genre) return NULL;
    else {
        Movie *movie = select_from_list<Movie*>(&genre->list); 
        return movie;
    }
}

LinkedList<Movie*>* Graph::recommend_movies(string title) {
    LinkedList<Movie*> *mov = movies.search(title);

    Movie *node = select_from_list<Movie*>(mov);
    delete mov;

    if (node) {
        int count = 0, index;
        auto genre = node->category.start;
        LinkedList<Movie*> *list = new LinkedList<Movie*>;
        
        while (genre)
        {
            count += genre->data->list.length;
            genre = genre->next;
        }

        MaxHeap<Movie*> *heap = new MaxHeap<Movie*>(count);

        genre = node->category.start;

        while (genre)
        {   
            auto movie = genre->data->list.start;

            while(movie) {
                if (title.compare(movie->data->name.data()) != 0) {
                    int index = heap->find_value(movie->data);

                    if (index == -1) {
                        heap->insert(1, movie->data);
                    } else {
                        heap->update_priority(index, heap->data[index]->priority + 1);
                    }
                }
                movie = movie->next;
            }
            genre = genre->next;
        }

        for (int i = 0; i < 5; i++) {
            auto temp = heap->pop();
            list->insert(temp->data);
            delete temp;
        }

        cout << "Similar movies: ";
        list->printList();
        delete list;
    }

    return NULL;
}

void Graph::printMovieDetails(Movie* movie)
{
    cout << "\033[2J\033[1;1H";
    cout << "#### MOVIE DETAILS #### " << endl;
    cout << "Title: " << movie->name << endl;
    cout << "Type: " << movie->type << endl;
    cout << "Directed by: ";
    movie->directors.printList();
    cout << "Actors: ";
    movie->actors.printList();
    cout << "Release year: " << movie->release_year << endl;
    cout << "Description: " << movie->description << endl;
}