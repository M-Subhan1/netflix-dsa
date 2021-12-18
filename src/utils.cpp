#include<iostream>
#include"../include/csv_parser.hpp"
#include"../include/movie.hpp"
#include"../include/utils.hpp"
#include"../include/trie.hpp"

using namespace std;

Movies* get_data (const char* file_name) {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    Movies *movies = new Movies(8000); Trie<Movie> *trie = new Trie<Movie>();
    Movie *temp;

    for (int i = 0; i < movies->size; i++) { 
        temp = new Movie();
        in.read_row(*temp->show_id, *temp->type, *temp->title, *temp->director, *temp->cast, *temp->country, *temp->date_added, *temp->release_year, *temp->rating, *temp->duration, *temp->listed_in, *temp->description);
        movies->list[i] = temp;
    }

    return movies;
}