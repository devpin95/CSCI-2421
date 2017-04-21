#ifndef BSTREE_
#define BSTREE_
#include <iostream>
using namespace std;
#include "Node.h"
#include "Entry.h"

// Binary Search Tree class
class BSTree {
private:
    Node* root;
    void addNode(Entry* key, Node* leaf);
    Node* deleteNode(Node* node, Entry* key);
    void freeNode(Node* leaf);
public:
    BSTree();
    ~BSTree();
    Node* Root() { return root; }
    void setRoot(Node * _root) {root = _root;}
    void addNode(Entry* key);
    Node* findNode(Entry* key, Node* parent);
    void printPreorder(Node* node);
    void printInorder(Node* node);
    void printPostorder(Node* node);
    

    void deleteNode(Entry* key);

    Node* min(Node* node);
    Node* max(Node* node);
    Node* successor(Entry* key, Node* parent);
    Node* predecessor(Entry* key, Node* parent);

};
#endif  //BST
