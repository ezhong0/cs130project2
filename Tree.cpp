#include "Tree.h"
#include <iostream>
#include <string>
#define MININT -2147483648
#define MAXINT 2147483647

AVLTree::AVLTree(){
    root = NULL;
}

AVLTree::~AVLTree(){
    deleteHelper(root);
}

void AVLTree::deleteHelper(Node* n){
    if(n == NULL)  
        return;
    deleteHelper(n->left);
    deleteHelper(n->right);
    delete(n);
}

Node* AVLTree::makeNode(const int key){
    Node* n = new Node();
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

int AVLTree::getHeight(Node* n){
    return (n == NULL) ? 0 : n->height;
}

Node* AVLTree::rotateLeft(Node* n){
    Node* r = n->right;
    Node* rl = r->left;
    r->left = n;
    n->right = rl;
    n->height = (getHeight(n->left)>getHeight(n->right)) ? getHeight(n->left)+1 : getHeight(n->right)+1;
    r->height = (getHeight(r->left)>getHeight(r->right)) ? getHeight(r->left)+1 : getHeight(r->right)+1;
    numRotations++;
    return r;
}

Node* AVLTree::rotateRight(Node* n){
    Node* l = n->left;
    Node* lr = n->right;
    l->right = n;
    n->left = lr;
    n->height = (getHeight(n->left)>getHeight(n->right)) ? getHeight(n->left)+1 : getHeight(n->right)+1;
    l->height = (getHeight(l->left)>getHeight(l->right)) ? getHeight(l->left)+1 : getHeight(l->right)+1;
    numRotations++;
    return l;
}

bool AVLTree::insert(int key){
    try{
        root = insert(root, key);
    }catch(int key){
        return false;
    }
    numAdded++;
    return true;
}

Node* AVLTree::insert(Node* n, int key){
    if(n == NULL)
        return makeNode(key);
    
    numVisited++;

    if(key < n->key)
        n->left = insert(n->left, key);
    else if(key > n->key)
        n->right = insert(n->right, key);
    else
        throw key;
    
    n->height = (getHeight(n->left)>getHeight(n->right)) ? getHeight(n->left)+1 : getHeight(n->right)+1;

    int balance = (n == NULL) ? 0 : getHeight(n->right) - getHeight(n->left);

    if(balance < -1 && key < n->left->key)
        return rotateRight(n);
    if(balance > 1 && key > n->right->key)
        return rotateLeft(n);
    if(balance < -1 && key > n->left->key){
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if(balance > 1 && key < n->right->key){
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

std::string AVLTree::print(){
    return printHelper(root, 0);
}

std::string AVLTree::printHelper(Node* n, int h){
    std::string result = "";
    for(int i=0; i<h; i++)
        result += " ";
    if(n == NULL){
        result += "NULL\n";
        return result;
    }

    if(n->left == NULL && n->right == NULL){
        result += "Leaf(" + std::to_string(n->key) + ")\n";
        return result;
    }

    result += "Node(" + std::to_string(n->key) + ", h=" + std::to_string(n->height-1) + "):\n" + printHelper(n->left, h+1) + printHelper(n->right, h+1);
    return result;
}

bool AVLTree::lookup(const int key){
    Node* curr = root;

    while(curr != NULL){
        numVisited++;
        if(key > curr->key)
            curr = curr->right;
        else if(key < curr->key)
            curr = curr->left;
        else
            return true;
    }
    return false;
}

int AVLTree::getMax(){
  Node* curr = root;
  while(curr->right != NULL)
	curr = curr->right;
  return curr->key;
}

int AVLTree::getMin(){
  Node* curr = root;
  while(curr->left != NULL)
	curr = curr->left;
  return curr->key;
}

void AVLTree::resetStats(){
    numAdded = 0;
    numVisited = 0;
    numRotations = 0;
}

int AVLTree::getNumAdded(){
    return numAdded;
}

int AVLTree::getNumRotations(){
    return numRotations;
}

int AVLTree::getNumVisited(){
    return numVisited;
}

std::string AVLTree::rangeLL(){
    std::string str = rangeLLHelper(root, MININT);
    str = str.substr(0, str.length() - 2);
    if(str.length() == 0)
        return "No inserts would cause a left-left rotation.\n";
    else
        return "The following inserts would cause a left-left rotation:\n" + str + "\n";
}

std::string AVLTree::rangeLLHelper(Node* n, int lb){
    if(n == NULL)
        return "";
    if(n->left == NULL)
        return rangeLLHelper(n->right, n->key);
    if(getHeight(n->right) - getHeight(n->left) == -1 && getHeight(n->left->right) - getHeight(n->left->left) != -1)
        return toTool(lb, n->left->key) + ", " + rangeLLHelper(n->right, n->key);
    else
        return rangeLLHelper(n->left, lb) + rangeLLHelper(n->right, n->key);
}

std::string AVLTree::rangeLR(){
    std::string str = rangeLRHelper(root);
    str = str.substr(0, str.length() - 2);
    if(str.length() == 0)
        return "No inserts would cause a left-right rotation.\n";
    else
        return "The following inserts would cause a left-right rotation:\n" + str + "\n";
}

std::string AVLTree::rangeLRHelper(Node* n){
    if(n == NULL)
        return "";
    if(n->left == NULL)
        return rangeLRHelper(n->right);
    if(getHeight(n->right) - getHeight(n->left) == -1 && getHeight(n->left->right) - getHeight(n->left->left) != 1)
        return toTool(n->left->key, n->key) + ", " + rangeLRHelper(n->right);
    else
        return rangeLRHelper(n->left) + rangeLRHelper(n->right);
}

std::string AVLTree::rangeRL(){
    std::string str = rangeRLHelper(root);
    str = str.substr(0, str.length() - 2);
    if(str.length() == 0)
        return "No inserts would cause a right-left rotation.\n";
    else
        return "The following inserts would cause a right-left rotation:\n" + str + "\n";
}

std::string AVLTree::rangeRLHelper(Node* n){
    if(n == NULL)
        return "";
    if(n->left == NULL)
        return rangeRLHelper(n->left);
    if(getHeight(n->right) - getHeight(n->left) == -1 && getHeight(n->left->right) - getHeight(n->left->left) != 1)
        return rangeRLHelper(n->right) + ", " + toTool(n->left->key, n->key);
    else
        return rangeRLHelper(n->left) + rangeRLHelper(n->right);
}

std::string AVLTree::rangeRR(){
    std::string str = rangeRRHelper(root, MAXINT);
    str = str.substr(0, str.length() - 2);
    if(str.length() == 0)
        return "No inserts would cause a right-right rotation.\n";
    else
        return "The following inserts would cause a right-right rotation:\n" + str + "\n";
}

std::string AVLTree::rangeRRHelper(Node* n, int ub){
    if(n == NULL)
        return "";
    if(n->right == NULL)
        return rangeRRHelper(n->left, ub);
    if((getHeight(n->right) - getHeight(n->left) == 1) && (getHeight(n->right->right) - getHeight(n->right->left) != 1))
        return rangeRRHelper(n->left, n->key) + toTool(n->right->key, ub) + ", ";
    return rangeRRHelper(n->left, n->key) + rangeRRHelper(n->right, ub);
}

std::string AVLTree::toTool(int left, int right){
    std::cout<<left<<right;
    if(left != MININT)
        left++;
    if(right != MAXINT)
        right--;
    if(left < right)
        return std::to_string(left) + " to " + std::to_string(right);
    if(left == right)
        return std::to_string(left);
    return "";
}
