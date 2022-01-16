#ifndef AVL_H
#define AVL_H

#include<iostream>
#include"SinglyLinkedList.hpp"
#include"trie.hpp"

using namespace std;

// template AVL that stores key value pairs
// Key template passed in as K, Data stored passed in as T

// Stores AVL Nodes
template <class K, class T> class AVLNode {
public:
    AVLNode<K,T> *lchild; // left_child of the node
    AVLNode<K,T> *rchild; // right_child of the node
	K key; // key (used in storing and retrieving data)
    T data; // data
    int height; // height of the node
    
    // construtor
    AVLNode(K key, T data) {
        lchild = rchild = NULL;
        this->data = data;
		this->key = key;
        height = 0;
    }
};

// Template AVL Tree
template <class K, class T> class AVL {
public:
    AVLNode<K,T> *root; // stores the root node
    AVLNode<K,T> *pLoc; // used in searching and update
    AVLNode<K,T> *loc; // used in searching and update
    AVL(); // constructor
    ~AVL(); //destrcutor
    T search(K); // searches for a value and updated pLoc and loc
    void insert(K, T); // inserts new nodes
    void remove(K); // removes the node against Key K
    void preOrderTraversal(AVLNode<K,T> *); // preorder traversla
    void inOrderTraversal(AVLNode<K,T> *); // inorder traversal
    void postOrderTraversal(AVLNode<K,T> *); // postorder traversal
    int calculateDepth(AVLNode<K,T> *, int = 0);  // calculates depth of a node of a AVL
    int calculateHeight(AVLNode<K,T> *); // calculates height of a AVL
    void destroyAVL(); // destorys AVL
    void tree_summary(); // abstraction layer for tree_summary
    AVLNode<K,T>* rotate(AVLNode<K,T>*);
    void destroyValues(AVLNode<K,T> *node);
private:
    int* tree_summary(AVLNode<K,T> *); // prints summary of the tree
    AVLNode<K,T>* insert(K, T, AVLNode<K,T> *, AVLNode<K,T> *);
    AVLNode<K,T>* remove(K, AVLNode<K,T> *, AVLNode<K,T> *);
    void remove_node(); // overloaded method to remove the node
    void destroyAVL(AVLNode<K,T>*); // main logic for destroying AVL
    void searchHelper(K, AVLNode<K,T>*, AVLNode<K,T>*); // search helper with main search logic
    AVLNode<K,T>* rrotation(AVLNode<K,T>*); // right rotate the tree about a node
    AVLNode<K,T>* lrotation(AVLNode<K,T>*); // left rotates the tree about a node
    AVLNode<K,T>* rlrotation(AVLNode<K,T>*); // rl rotates the tree
    AVLNode<K,T>* lrrotation(AVLNode<K,T>*); // lr rotates a tree
    int balance_factor(AVLNode<K,T>*); // calculates vbalance factor of a node
};

template <class K, class T> AVL<K, T>::AVL() {
    root = pLoc = loc = NULL; // init pointers to null
}

template <class K, class T> AVL<K, T>::~AVL() {
    destroyAVL(); // call destroy bst function
}

template <class K, class T> void AVL<K, T>::destroyAVL() {
    destroyAVL(root); // call overload bst func with main logic
    root = NULL; // update root to null
}
// destory bst func with main logic
template <class K, class T> void AVL<K, T>::destroyAVL(AVLNode<K,T>* curr) {
    // destroy in post order traversal
    if (curr) {
        destroyAVL(curr->lchild);
        destroyAVL(curr->rchild);
        delete curr;
    }
}

template <class K, class T> T AVL<K, T>::search(K key) {
    // init pointers with null and call search helper (recursive)
    loc = NULL;
    pLoc = NULL;

    searchHelper(key, NULL, root);
	if (!loc) return NULL; // if no data, return NULL
	return loc->data;
}

template <class K, class T> void AVL<K, T>::searchHelper(K key, AVLNode<K, T> *prev, AVLNode<K, T> *curr) {
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

template <class K, class T> void AVL<K, T>::insert(K key, T data) { // provides abstraction for the user
    insert(key, data, NULL, root); // calls overloaded insert function
}

template <class K, class T> AVLNode<K, T>* AVL<K, T>::insert(K key, T data, AVLNode<K, T> *prev, AVLNode<K, T> *curr) {
    if (!curr) {
        AVLNode<K, T> *node = new AVLNode<K, T>(key, data);

        if (!root) root = node;
        else if (key < prev->key) prev->lchild = node;
        else if (key > prev->key) prev->rchild = node;

        return node;
    }
        
    if (key == curr->key) return curr;
    if (key < curr->key) curr->lchild = insert(key, data, curr, curr->lchild);
    else if (key > curr->key) curr->rchild = insert(key, data, curr, curr->rchild);
    
    // rotates the tree after insertion
    if (curr == root)  { 
        root = rotate(curr); 
        return root;
    }

    return rotate(curr); // returns new sub-tree root
};

template <class K, class T> void AVL<K, T>::remove(K key) {
    remove(key, NULL, root);
}

template <class K, class T> AVLNode<K, T>* AVL<K, T>::remove(K key, AVLNode<K, T> *prev, AVLNode<K, T> *curr) {
    if (!curr) return curr;
        
    if (key == curr->key) {
        loc = curr;
        pLoc = prev;
        // deleting a leaf node
        if (!loc->lchild && !loc->rchild) {
            // if leaf is also a root
            if (!pLoc) root = NULL;
            // leaf is on the left branch of its predecessor
            else if (pLoc->lchild == loc) pLoc->lchild = NULL;
            // leaf on the right branch of its predecessor
            else  pLoc->rchild = NULL;
        // deleting a node with only the right subtree
        } else if (!loc->lchild) {
            if (!pLoc) root = loc->rchild;
            // leaf is on the left branch of its predecessor
            else if (pLoc->lchild == loc) pLoc->lchild = loc->rchild;
            // leaf on the right branch of its predecessor
            else  pLoc->rchild = pLoc->rchild = loc->rchild;
        // deleting a node with only the left subtree
        } else if (!loc->rchild) {
            if (!pLoc) root = loc->lchild;
            // leaf is on the left branch of its predecessor
            else if (pLoc->lchild == loc) pLoc->lchild = loc->lchild;
            // leaf on the right branch of its predecessor
            else  pLoc->rchild = pLoc->rchild = loc->lchild;
        // deleting a node with both children
        } else {
            AVLNode<K,T> *prev = loc;
            AVLNode<K,T> *curr = loc->lchild; // selecting lchild of the loc
            // finding the logical predecessor of the loc
            while(curr && curr->rchild) {
                prev = curr;
                curr = curr->rchild;
            };

            // breaking links with prev nodes
            if (loc == prev) loc->lchild = NULL;
            else prev->rchild = NULL;

            // updating pointers for replacement node
            curr->lchild = loc->lchild;
            curr->rchild = loc->rchild;

            // place the node in the tree
            if (!pLoc) root = curr;
            else if (pLoc->lchild == loc) pLoc->lchild = curr;
            else if (pLoc->rchild == loc) pLoc->rchild = curr;
        }
        delete loc; // delete loc
        return NULL;
    }

    if (key < curr->key) curr->lchild = remove(key, curr, curr->lchild);
    else if (key > curr->key) curr->rchild = remove(key, curr, curr->rchild);
    
    if (curr == root)  { 
        root = rotate(curr); 
        return root;
    }

    return rotate(curr);
}

template <class K, class T> void AVL<K, T>::preOrderTraversal(AVLNode<K,T> *curr) {
    if (curr) {
        // first print then traverse left and right
        cout << curr->data << " ";
        preOrderTraversal(curr->lchild);
        preOrderTraversal(curr->rchild);
    }
} 

template <class K, class T> void AVL<K, T>::inOrderTraversal(AVLNode<K,T> *curr) {
    if (curr) {
        // traverse left, print and then traverse right
        inOrderTraversal(curr->lchild);
        cout << curr->data << " ";
        inOrderTraversal(curr->rchild);
    }
}

template <class K, class T> void AVL<K, T>::postOrderTraversal(AVLNode<K,T> *curr) {
    if (curr) {
        // traverse left, right and then print
        postOrderTraversal(curr->lchild);
        postOrderTraversal(curr->rchild);
        cout << curr->data << " ";
    }
}

template <class K, class T> int AVL<K, T>::calculateHeight(AVLNode<K,T> *curr) {
    if (!curr) return -1; // if tree empty return -1
    if (!curr->lchild && !curr->rchild) return 0;

    if (curr->lchild && curr->rchild) {
        int val1 = curr->lchild->height;
        int val2 = curr->rchild->height;
        return val1 > val2 ? val1 + 1 : val2 + 1; // retun height of bigger branch
    } 
    
    if (curr->lchild) return curr->lchild->height + 1;
    return curr->rchild->height + 1;
}

template <class K, class T> int AVL<K, T>::calculateDepth(AVLNode<K,T> *curr, int count) {
    if (curr == root) return 0; // if curr == root, depth == 0
    if (!root || !curr) return -1; // if no root, return -1
    search(curr->data); // set pLoc to parent node
    return 1 + calculateDepth(pLoc, count); // depth of a node = depth of its parent node + 1
}

template <class K, class T> AVLNode<K, T>* AVL<K, T>::rotate(AVLNode<K, T>* curr) {
    if (!curr) return NULL;

    int balance = balance_factor(curr);

    if (balance == -2 && balance_factor(curr->rchild) == -1) return lrotation(curr);

    else if (balance == -2 && balance_factor(curr->rchild) == 1) return rlrotation(curr);
    
    else if (balance == 2 && balance_factor(curr->lchild) == 1) return rrotation(curr);
    
    else if (balance == 2 && balance_factor(curr->lchild) == -1) return lrrotation(curr);

    curr->height = calculateHeight(curr);
    return curr;
}

template <class K, class T> AVLNode<K,T>* AVL<K,T>::rrotation(AVLNode<K,T>* curr) {
    if (!curr) return curr;
    AVLNode<K, T>* nroot = curr->lchild;
    
    curr->lchild = nroot->rchild;
    nroot->rchild = curr;

    curr->height = calculateHeight(curr);
    nroot->height = calculateHeight(nroot);

    return nroot;
}

template <class K, class T> AVLNode<K,T>* AVL<K,T>::lrotation(AVLNode<K,T>* curr) {
    if (!curr) return curr;
    AVLNode<K, T>* nroot = curr->rchild;
    
    curr->rchild = nroot->lchild;
    nroot->lchild = curr;

    curr->height = calculateHeight(curr);
    nroot->height = calculateHeight(nroot);

    return nroot;
}

template <class K, class T> AVLNode<K,T>* AVL<K,T>::rlrotation(AVLNode<K,T>* curr) {
    curr->rchild = rrotation(curr->rchild);
    return lrotation(curr);
}

template <class K, class T> AVLNode<K,T>* AVL<K,T>::lrrotation(AVLNode<K,T>* curr) {
    curr->lchild = lrotation(curr->lchild);
    return rrotation(curr);
}

template <class K, class T> int  AVL<K, T>::balance_factor(AVLNode<K, T>* curr) {
    if (!curr) return 0;
    return calculateHeight(curr->lchild) - calculateHeight(curr->rchild);
}

template <class K, class T> void AVL<K, T>::tree_summary() {
    int *arr = tree_summary(root);
    cout << "Number of nodes with only the left child: " << arr[0] << endl;
    cout << "Number of nodes with only the right child: " << arr[1] << endl;
    cout << "Number of nodes with both children: " << arr[2] << endl;
    cout << "Number of Leaves: " << arr[3] << endl;

    delete[] arr;
}

template <class K, class T> int* AVL<K, T>::tree_summary(AVLNode<K, T> *curr) {
    int *arr = new int[4]; 
    arr[0] = arr[1] = arr[2] = arr[3] = 0;
    // arr[0] = left, arr[1] = right, arr[2] = both, arr[3] = leaf
    if (!curr) return arr;

    int *arrL = tree_summary(curr->lchild);
    int *arrR = tree_summary(curr->rchild);

    if (curr->lchild && curr->rchild) arr[2]++;
    else if (!curr->rchild && curr->lchild) arr[0]++;
    else if (curr->rchild && !curr->lchild) arr[1]++;
    else arr[3]++;

    for (int i = 0; i < 4; i++) arr[i] = arr[i] + arrL[i] + arrR[i];
    delete[] arrL; delete[] arrR;
    return arr;
}

template <class K, class T> void AVL<K, T>::destroyValues(AVLNode<K,T> *node) {
    if (node) {
        destroyValues(node->lchild);
        destroyValues(node->rchild);
        delete node->data;
    }
}

#endif