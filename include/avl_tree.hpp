#ifndef AVL_H
#define AVL_H

#include<iostream>

using namespace std;

template <class T> class AVLNode {
public:
    AVLNode<T> *lchild;
    AVLNode<T> *rchild;
	char key;
    T data;
    AVLNode(char key, T data) {
        lchild = rchild = NULL;
        this->data = data;
		this->key = key;
    }
};

template <class T> class AVL {
public:
    AVLNode<T> *root;
    AVLNode<T> *pLoc;
    AVLNode<T> *loc;
    AVL();
    ~AVL();
    T search(char key); // searches for a value and updated pLoc and loc
    void insert(char, T); // inserts new nodes
    void inOrderTraversal(AVLNode<T> *); // inorder traversal
    int calculateHeight(AVLNode<T> *); // calculates height of a AVL
    void destroyAVL(); // destorys AVL
private:
    void destroyAVL(AVLNode<T>*); // main logic for destroying AVL
    void searchHelper(char, AVLNode<T>*, AVLNode<T>*); // search helper with main search logic
};

template <class T> AVL<T>::AVL() {
    root = pLoc = loc = NULL; // init pointers to null
}

template <class T> AVL<T>::~AVL() {
    destroyAVL(); // call destroy bst function
}

template <class T> void AVL<T>::destroyAVL() {
    destroyAVL(root); // call overload bst func with main logic
    root = NULL; // update root to null
}
// destory bst func with main logic
template <class T> void AVL<T>::destroyAVL(AVLNode<T>* curr) {
    // destroy in post order traversal
    if (curr) {
        destroyAVL(curr->lchild);
        destroyAVL(curr->rchild);
        delete curr;
    }
}

template <class T> T AVL<T>::search(char key) {
    // init pointers with null and call search helper (recursive)
    loc = NULL;
    pLoc = NULL;
    searchHelper(key, NULL, root);
	if (!loc) return NULL;
	return loc->data;
}

template <class T> void AVL<T>::searchHelper(char key, AVLNode<T> *prev, AVLNode<T> *curr) {
    // curr null, no more nodes to traverse, so set loc = nULL and pLoc to its logical predecessor
    if (curr == NULL) {
        loc = NULL;
        pLoc = prev;
    } else if (curr->key == key) { // if data found set loc to curr, pLoc to prev
        loc = curr;
        pLoc = prev;
    } else if (key < curr->key) { // if data < curr->data, search left branch
        searchHelper(key, curr, curr->lchild);
    } else if (key > curr->key) { // if data > curr->data, search right branch
        searchHelper(key, curr, curr->rchild);
    }
}

template <class T> void AVL<T>::insert(char key, T data) {
    search(key); // call search to set loc and Ploc

    if (loc != NULL) return; // if value exists, return
    AVLNode<T> *node = new AVLNode<T>(key, data); // create new node
	
    if (pLoc == NULL) root = node; // if pLoc == null, tree is empty, make node the root
    else if (key < pLoc->key) pLoc->lchild = node; // if data < predecessor, insert in left branch
    else pLoc->rchild = node; // if data > pred, insert in rgiht branch
}

template <class T> void AVL<T>::inOrderTraversal(AVLNode<T> *curr) {
    if (curr) {
        // traverse left, print and then traverse right
        inOrderTraversal(curr->lchild);
        cout << *(curr->data) << " ";
        inOrderTraversal(curr->rchild);
    }
}

template <class T> int AVL<T>::calculateHeight(AVLNode<T> *curr) {
    if (!curr) return -1; // if tree empty return -1
    int val1 = calculateHeight(curr->lchild); // calc height of left branch
    int val2 = calculateHeight(curr->rchild); // calc height of right branch
    return val1 > val2 ? val1 + 1 : val2 + 1; // retun height of bigger branch
}

#endif