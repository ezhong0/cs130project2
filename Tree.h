#ifndef TREE_H
#define TREE_H
#include <string>

class Node{
    public:
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree{
    Node* root; 

    int numAdded;
    int numVisited;
    int numRotations;

    Node* makeNode(const int key);
    int getHeight(Node* n);

    void deleteHelper(Node* n);

    Node* rotateRight(Node* n);
    Node* rotateLeft(Node* n);
    Node* insert(Node* n, int key);

    std::string printHelper(Node* n, int h);
    std::string rangeLLHelper(Node* n, int lb);
    std::string rangeLRHelper(Node* n);
    std::string rangeRLHelper(Node* n);
    std::string rangeRRHelper(Node* n, int ub);

    std::string toTool(int left, int right);

    public:
    AVLTree();
    ~AVLTree();
    int getNumAdded();
    int getNumVisited();
    int getNumRotations();

    int getMax();
    int getMin();
    void resetStats();

    bool insert(const int key);
    bool lookup(const int key);

    std::string print();
    std::string rangeLL();
    std::string rangeLR();
    std::string rangeRL();
    std::string rangeRR();
    

};

#endif
