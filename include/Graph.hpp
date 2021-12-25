#include<iostream>
#include"trie.hpp"
#include"SinglyLinkedList.hpp"

using namespace std;

template <class K, class T> class GraphNode {
    T data;
    LinkedList<GraphNode<K,T>*> edges;
};

template <class K, class T>class Graph {
    Trie<GraphNode<K,T>*> data;
    void insert(K key, T data);
    void remove_node(K key);
    T search(K key);
    int get_weight(K, K);
    void insert_edge(K, K);
    void remove_edge(K, K);
};

template <class K, class T> void Graph<K, T>::insert(K key, T value) {
    GraphNode<K, T> *node = new GraphNode<K, T>(value);
    data->insert(key, node);
}

template <class K, class T> void Graph<K, T>::remove_node(K key) {
    GraphNode<K, T>* node = data->search(key);
    // remove edges
    data->remove(key);
}

template <class K, class T> T Graph<K, T>::search(K key) {
    GraphNode<K, T>* node = data->search(K);
    return node ? node->data: NULL;
}

template <class K, class T> int Graph<K, T>::get_weight(K key_node1, K key_node2) {
    GraphNode<K, T> *node1, *node2;
    node1 = data->search(key_node1);
    node2 = data->search(key_node2);

    if (!node1 || !node2) return 0;
    return 1;
}

template <class K, class T> void Graph<K, T>::insert_edge(K key_node1, K key_node2) {
    GraphNode<K, T> *node1, *node2;
    node1 = data->search(key_node1);
    node2 = data->search(key_node2);

    if (!node1 || !node2) return;
}

template <class K, class T> void Graph<K, T>::remove_edge(K key_node1, K key_node2) {
    GraphNode<K, T> *node1, *node2;
    node1 = data->search(key_node1);
    node2 = data->search(key_node2);

    if (!node1 || !node2) return;
}