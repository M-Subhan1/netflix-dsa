#include<iostream>
#include"../include/csv_parser.hpp"
#include"../include/movie.hpp"
#include"../include/utils.hpp"
#include"../include/trie.hpp"
#include"../include/SinglyLinkedList.hpp"

using namespace std;

LinkedList<Movie*>* get_data (const char* file_name) {
    io::CSVReader<12, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("./data/netflix_titles.csv");
    in.read_header(io::ignore_extra_column, "show_id", "type", "title", "director", "cast", "country", "date_added", "release_year", "rating", "duration", "listed_in", "description");
    LinkedList<Movie*> *movies = new LinkedList<Movie*>;
    string cast, listed_in;
    Movie *temp;

    while (true) {
        temp = new Movie();
        if (!in.read_row(temp->show_id, temp->type, temp->title, temp->director, cast, temp->country, temp->date_added, temp->release_year, temp->rating, temp->duration, listed_in, temp->description)) 
            break;

        temp->listed_in = parse_multivalued_attr(listed_in);
        temp->cast = parse_multivalued_attr(cast);
        movies->insert(temp);
    }

    return movies;
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