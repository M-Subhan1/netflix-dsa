#include"../include/Graph.hpp"
#include"../include/utils.hpp"

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
    delete list;
    if (movie) {
        printMovieDetails(movie);
    }
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
    
}

void Graph::printMovieDetails(Movie* movie)
{
    cout << "Title: " << movie->name << endl;
    cout << "Type: " << movie->type << endl;
    cout << "Directed by: ";
    movie->directors.printList();  cout << endl;
    cout << "Actors: ";
    movie->actors.printList();
    cout << "Release year: " << movie->release_year << endl;
    cout << "Description: " << movie->description << endl;
}