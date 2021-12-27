#ifndef UTILS_H
#define UTILS_H
#include"trie.hpp"
#include"movie.hpp"
#include"SinglyLinkedList.hpp"

LinkedList<Movie*>* get_data ();
LinkedList<std::string>* parse_multivalued_attr(string string);

#endif