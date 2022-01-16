#ifndef HEAP_H
#define HEAP_H
#include<iostream>

using namespace std;

template <class T> class HeapNode {
public:
    int priority; // stores priority of the node
    T data; // stores data

    HeapNode(int priority = NULL, T data = NULL) { // constructor
        this->priority = priority;
        this->data = data;
    }
};

template <class T> class MaxHeap {
public:
    int num_el; // number of elements in the heap
    int size; // max elements in the heap
    HeapNode<T> **data; // Pointer to an Array of Heap Node *

    MaxHeap(int size) {
        this->size = size;
        num_el = 0;
        data = new HeapNode<T>* [size]; // init Array of HeapNode*
    }

    void insert(int priority, T data) { // insert data with its priority
        if (num_el == size) return;
        HeapNode<T> *node = new HeapNode<T>(priority, data);
        this->data[num_el++] = node;
        bubble_up(num_el - 1);
    }

    HeapNode<T> *pop() { // remove heap node and update heap
        if (!num_el) return NULL;
        HeapNode<T> *node = data[0];
        data[0] = data[num_el - 1];
        data[num_el - 1] = 0;
        num_el--;
        bubble_down(0);
        return node;
    }

    void bubble_up(int index) { // bubble up felement at the provided index
        if (num_el == 0 || index < 0 || index > num_el) return;
        int ichild = index;
        int iparent = get_parent(index);
        
        HeapNode<T>* temp = NULL;

        while (ichild != 0 && data[ichild]->priority >= data[iparent]->priority)
        {   
            temp = data[ichild];
            data[ichild] = data[iparent];
            data[iparent] = temp;
            ichild = iparent;
            iparent = get_parent(ichild);
        }
    }

    void bubble_down(int index) { // bubble down the element at the given index
        if (num_el == 0 || index < 0 || index > num_el) return;
        int iparent = index;
        int ilchild = get_lchild(index);
        int irchild = get_rchild(index);
        int ichild = ilchild >= irchild ? ilchild : irchild;

        HeapNode<T>* temp = NULL;

        while (ichild < num_el && data[ichild]->priority >= data[iparent]->priority)
        {   
            temp = data[ichild];
            data[ichild] = data[iparent];
            data[iparent] = temp;
            iparent = ichild;
            ilchild = get_lchild(iparent);
            irchild = get_rchild(iparent);
            ichild = ilchild >= irchild ? ilchild : irchild;
        }
    }

    int get_parent(int index) { // calculate parent of a given index
        return (index - 1) / 2;
    }

    int get_lchild(int index) { // calculate index of lchild of an index
        return 2 * index + 1;
    }

    int get_rchild(int index) { // calculate index of rchild of an index
        return 2 * index + 2;
    }

    int find_value(T val) { // find a value
        for (int i = 0; i < num_el; i++) {
            if (data[i] && data[i]->data == val) return i;
        }
        return -1;
    }

    void update_priority(int index, int priority) { // update priority of a node
        data[index]->priority = priority;
        bubble_up(index);
    }

    ~MaxHeap() { // destroy heap, deallocate space
        if (!data) return;
        for (int i = 0; i < num_el; i++) delete data[i];
        delete[] data;
        data = NULL;
    }
};

#endif