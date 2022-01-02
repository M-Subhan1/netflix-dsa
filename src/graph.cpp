#include"../include/Graph.hpp"

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

Movie *Graph::search_by_director(string name) {
    LinkedList<Director<Movie*>*> *list = directors.search(name);
    // list->printList();
    // if (list) delete list;
    return NULL;
}

Movie *Graph::search_by_actor(string name) {
    LinkedList<Actor<Movie*>*> *list = actors.search(name);
    // list->printList();
    // delete list;
    return NULL;
}

Movie *Graph::search_by_title(string title) {
    LinkedList<Movie*> *list = movies.search(title);
    return NULL;
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