#include "Tree.h"
#include <iostream>
#include <windows.h>

Tree::Tree(){
    this->setRoot(NULL);
    this->setMin(1000);
    this->setMax(-1000);
    this->setAverage(0);
    this->setNodeCount(0);
}

Tree::~Tree(){
}

void Tree::setRoot(Node* root){
    this->root = root;
}
Tree::Node* Tree::getRoot() const{
    return this->root;
}
void Tree::setMin(int minValue){
    this->minValue = minValue;
}
int Tree::getMin() const{
    return this->minValue;
}
void Tree::setMax(int maxValue){
    this->maxValue = maxValue;
}
int Tree::getMax() const{
    return this->maxValue;
}
void Tree::setNodeCount(int nodeCount){
    this->nodeCount = nodeCount;
}
int Tree::getNodeCount() const{
    return this->nodeCount;
}
void Tree::setAverage(float average){
    this->average = average;
}
float Tree::getAverage() const{
    return this->average;
}
void Tree::setIsAVL(bool value){
    this->isAVL = value;
}
bool Tree::getIsAVL() const{
    return this->isAVL;
}

void Tree::incrementNodeCount(){
    this->nodeCount++;
}

Tree::Node* Tree::createNode(int value){
    Node* newNode = new Node;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void Tree::addNode(int value){
    addNodePrivate(value, this->root);
}

void Tree::addNodePrivate(int value, Node* node){
    if(root == NULL){
        this->setRoot(createNode(value));
    }else if(value < node->value){
        if(node->left != NULL){
            //Recursively call function, to get node position
            addNodePrivate(value, node->left);
        }else{
            node->left = createNode(value);
        }
    }else if(value > node->value){
        if(node->right != NULL){
            //Recursively call function, to get node position
            addNodePrivate(value, node->right);
        }else{
            node->right = createNode(value);
        }
    }else{
        setColor(12);
        std::cout << "This tree only accepts unqiue values. [Error for value: " << value << "]" << std::endl;
        setColor(7);
    }
}

void Tree::printStats(){
    printStatsPrivate(this->root);
}

void Tree::printStatsPrivate(Node* node){
    int height = 0;

    if(this->root == NULL){
        return;
    }
    if(node->right != NULL){
        printStatsPrivate(node->right);
    }
    if(node->left != NULL){
        printStatsPrivate(node->left);
    }

    int balance = getBalancePrivate(node, height);
    std::cout << "bal("<< node->value << ") = " << balance;
    //Check AVL-Balance of node
    if(std::abs(balance) > 1){
        setColor(12); std::cout << " (AVL Violation!)" << std::endl; setColor(7);
        this->setIsAVL(false);
    }else
        std::cout << std::endl;

    //Calculate Stats
    if(this->minValue > node->value)
        this->setMin(node->value);
    if(maxValue < node->value)
        this->setMax(node->value);
    this->setAverage(this->getAverage() + node->value);
    this->incrementNodeCount();

    if(node == root){
        this->setAverage(this->getAverage() / this->getNodeCount());
        std::string avl = this->getIsAVL() ? "yes" : "no";
        std::cout << "--------------------------" << std::endl;
        std::cout << "AVL: " << avl << std::endl;
        std::cout << "min: " << this->getMin() << ", ";
        std::cout << "max: " << this->getMax() << ", ";
        std::cout << "avg: " << this->getAverage() << std::endl;
    }
}

int Tree::getBalancePrivate(Node* node, int &height){
    int leftHeight = 0, rightHeight = 0;

    if(node == NULL){
        //Leaf node is reached
        height = 0;
        return 0;
    }
    //Recursively calculate height of left and right subtrees of node
    getBalancePrivate(node->left, leftHeight);
    getBalancePrivate(node->right, rightHeight);
    height = std::max(leftHeight, rightHeight) + 1;

    //Return balance-factor of node
    return rightHeight - leftHeight;
}

bool Tree::searchNode(Node* nodeSearch, Node* nodeSubtree){
    bool isFound = true;

    if(nodeSearch == NULL){
        return false;
    }
    //Compare value of current node to searched node
    if(nodeSubtree->value < nodeSearch->value){
        if(nodeSearch->left != NULL){
            isFound = searchNode(nodeSearch->left, nodeSubtree);
        }else
            isFound = false;
    }else if(nodeSubtree->value > nodeSearch->value){
        if(nodeSearch->right != NULL){
            isFound = searchNode(nodeSearch->right, nodeSubtree);
        }else
            isFound = false;
    }

    return isFound;
}

bool Tree::searchSubtree(Node *nodeSearch, Node* nodeSubtree){
    //An empty tree is always a subtree of a tree
    //All elements of subtree are found in searchtree
    if (nodeSubtree == NULL)
        return true;
    //Searchtree has no more children, while subtree has not been entirely found
    if (nodeSearch == NULL)
        return false;

    //Node of subtree has been found in searchtree
    //Search left and right subtrees of searchtree for next elements in subtree
    if (nodeSearch->value == nodeSubtree->value)
        return searchSubtree(nodeSearch->left, nodeSubtree->left) &&
               searchSubtree(nodeSearch->right, nodeSubtree->right);

    //Element has not been found in searchtree
    //Check left and right subtree in searchtree until a different case is called
    return searchSubtree(nodeSearch->left, nodeSubtree) ||
           searchSubtree(nodeSearch->right, nodeSubtree);
}

void Tree::setColor(int i){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}




