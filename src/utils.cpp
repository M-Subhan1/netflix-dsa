#include<iostream>
#include"../include/csv_parser.hpp"
#include"../include/movie.hpp"
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/SinglyLinkedList.hpp"
#include"../include/Graph.hpp"
#include "../include/actor.hpp"

using namespace std;

Graph* get_graph (LinkedList<Movie*> *movies, LinkedList<Actor<Movie*>*> *actors, LinkedList<Director<Movie*>*> *directors, LinkedList<Genre<Movie*>*> *genres) {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    // LinkedList<Movie*> *movies = new LinkedList<Movie*>;
    Graph *graph = new Graph;
    string cast, genre, director;
    int x = 0;

    while (true && x < 100) {
        Movie *temp = new Movie;
        if (!in.read_row(temp->show_id, temp->type, temp->name, director, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, genre, temp->description)) {
            delete temp;
            break;
        }

        movies->insert(temp);
        parse_genre(genre, temp, graph, genres);
        parse_actor(cast, temp, graph, actors);
        parse_directors(director, temp, graph, directors);
        x++;
    }

    return graph;
}

void parse_genre(string str, Movie *movie, Graph *graph, LinkedList<Genre<Movie*>*> *genres) {
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Genre<Movie*> *genre = graph->add_category(temp);
            genres->insert(genre);
            genre->list.insert(movie); //insertion in list of movies stored in genre object
            movie->category.insert(genre);
            graph->add_movie(movie);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last genre left in parsed string
    if (temp.length()) {
        Genre<Movie*> *genre = graph->add_category(temp);
        genres->insert(genre);
        movie->category.insert(genre);
        genre->list.insert(movie);
        graph->add_movie(movie);
    }
}

void parse_actor(string str, Movie* movie, Graph *graph, LinkedList<Actor<Movie*>*> *actors)
{
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Actor<Movie*> *actor = graph->add_actor(temp.data());
            actors->insert(actor);
            actor->movie_list.insert(movie); //insertion in list of movies stored in genre object
            movie->actors.insert(actor);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last genre left in parsed string
    if (temp.length()) {
        Actor<Movie*> *actor = graph->add_actor(temp.data());        
        actors->insert(actor);
        actor->movie_list.insert(movie);
        movie->actors.insert(actor);
    }
}

void parse_directors(string str, Movie* movie, Graph *graph, LinkedList<Director<Movie*>*> *directors)
{
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Director<Movie*> *director = graph->add_director(temp.data());
            directors->insert(director);
            director->movie_list.insert(movie); //insertion in list of movies stored in director object
            movie->directors.insert(director);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }
    //adding the last director left in parsed string
    if (temp.length()) {
        Director<Movie*> *director = graph->add_director(temp.data());
        directors->insert(director);
        director->movie_list.insert(movie); //insertion in list of movies stored in director object
        movie->directors.insert(director);
    }
}
