#include<iostream>
#include"../include/csv_parser.hpp"
#include"../include/movie.hpp"
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/SinglyLinkedList.hpp"
#include"../include/Graph.hpp"

using namespace std;

Graph<Movie*>* get_data () {
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

void parse_genre(string str, Movie *movie, Graph<Movie*> *graph) {
    LinkedList<Genre<Movie*>> *list = new LinkedList<Genre<Movie*>>;
    std::string temp;

    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ',') {
            Genre<Movie*> *genre = graph->add_category(temp);
            genre->list.insert(movie);
            movie->category.insert(genre);
            graph->add_node(movie);
            temp = "";
        }
        else if (temp.empty() && str.at(i) == ' ') continue;
        else temp += str.at(i);
    }

    if (temp.length()) {
        Genre<Movie*> *genre = graph->add_category(temp);
        movie->category.insert(genre);
        genre->list.insert(movie);
        graph->add_node(movie);
    }
}

void parse_actor(string cast, Movie*, Graph<Actor*> *) {

}