#include<iostream>
#include"../include/csv_parser.hpp"
#include"../include/movie.hpp"
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/SinglyLinkedList.hpp"
#include"../include/Graph.hpp"
#include "../include/Graph(Actor).hpp"
#include "../include/actor.hpp"

using namespace std;

Graph<Movie*>* get_genre () {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    // LinkedList<Movie*> *movies = new LinkedList<Movie*>;
    Graph<Movie*> *graph = new Graph<Movie*>;
    string cast, genre;

    while (true) {
        Movie *temp = new Movie;
        if (!in.read_row(temp->show_id, temp->type, temp->title, temp->director, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, genre, temp->description)) {
            delete temp;
            break;
        }

        parse_genre(genre, temp, graph);
    }

    return graph;
}

ActorGraph<Movie*>* get_cast () {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    // LinkedList<Movie*> *movies = new LinkedList<Movie*>;
    ActorGraph<Movie*> *graph = new ActorGraph<Movie*>;
    string cast, genre;

    while (true) {
        Movie *temp = new Movie;
        if (!in.read_row(temp->show_id, temp->type, temp->title, temp->director, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, genre, temp->description)) {
            delete temp;
            break;
        }

        parse_actor(cast, temp, graph);
    }

    return graph;
}

LinkedList<std::string>* parse_multivalued_attr(string str) {
    LinkedList<std::string> *list = new LinkedList<string>;
    std::string temp;  
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            list->insert(temp);
            temp.assign("");
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }

    if (temp.length()) list->insert(temp);

    return list;
}

LinkedList<Movie*>* get_movies () {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    LinkedList<Movie*>* movies = new LinkedList<Movie*>;
    string cast, listed_in;

    while (true) {
        Movie *temp = new Movie;
        if (!in.read_row(temp->show_id, temp->type, temp->title, temp->director, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, listed_in, temp->description)) {
            delete temp;
            break;
        }

        temp->genres = parse_multivalued_attr(listed_in);
        temp->cast = parse_multivalued_attr(cast);
        movies->insert(temp);
    }

    return movies;    
}

void parse_genre(string str, Movie *movie, Graph<Movie*> *graph) {
    LinkedList<Genre<Movie*>> *list = new LinkedList<Genre<Movie*>>;
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Genre<Movie*> *genre = graph->add_category(temp);
            genre->list.insert(movie); //insertion in list of movies stored in genre object
            movie->category.insert(genre);
            graph->add_node(movie);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last genre left in parsed string
    if (temp.length()) {
        Genre<Movie*> *genre = graph->add_category(temp);
        movie->category.insert(genre);
        genre->list.insert(movie);
        graph->add_node(movie);
    }
}

void parse_actor(string str, Movie* movie, ActorGraph<Movie*> *graph)
{
    LinkedList<Actor<Movie*>> *list = new LinkedList<Actor<Movie*>>; //list of pointers of actors
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Actor<Movie*> *actor = graph->add_actor(temp);
            actor->movie_list.insert(movie); //insertion in list of movies stored in genre object
            movie->actors.insert(actor);
            graph->add_node(movie);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last genre left in parsed string
    if (temp.length()) {
        Actor<Movie*> *actor = graph->add_actor(temp);
        movie->actors.insert(actor);
        actor->movie_list.insert(movie);
        graph->add_node(movie);
    }
}

void parse_directors(string str, Movie* movie, DirectorGraph<Movie*> *graph)
{
    LinkedList<Director<Movie*>> *list = new LinkedList<Director<Movie*>>; //list of pointers of actors
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Director<Movie*> *director = graph->add_director(temp);
            director->movie_list.insert(movie); //insertion in list of movies stored in director object
            movie->directors.insert(director);
            graph->add_node(movie);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last director left in parsed string
    if (temp.length()) {
        Director<Movie*> *director = graph->add_director(temp);
        movie->directors.insert(director);
        director->movie_list.insert(movie);
        graph->add_node(movie);
    }
}

DirectorGraph<Movie*> *get_directors()
{
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    DirectorGraph<Movie*> *graph = new DirectorGraph<Movie*>;
    string cast, genre, directors;

    while (true) {
        Movie *temp = new Movie;
        if (!in.read_row(temp->show_id, temp->type, temp->title, directors, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, genre, temp->description)) {
            delete temp;
            break;
        }

        parse_directors(directors, temp, graph);
    }

    return graph;
}