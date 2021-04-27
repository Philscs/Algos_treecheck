#include "Tree.h"
#include <iostream>

Tree::Tree(){
    this->root = NULL;
    this->setMin(1000);
    this->setMax(-1000);
    this->setAverage(0);
    this->setNodeCount(0);
}

Tree::~Tree(){
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
        root = createNode(value);
    }else if(value < node->value){
        if(node->left != NULL){
            //Recursively call function, to get node position
            addNodePrivate(value, node->left);
        }else{
            node->left = createNode(value);
        }
    }else if(value > node->value){
        if(node->right != NULL){
            addNodePrivate(value, node->right);
        }else{
            node->right = createNode(value);
        }
    }else{
        std::cout << "This tree only accepts unqiue values. [Error for value: " << value << "]" << std::endl;
    }
}

void Tree::printStats(){
    printStatsPrivate(this->root);
}

void Tree::printStatsPrivate(Node* node){
    if(this->root == NULL){
        return;
    }
    if(node->right != NULL){
        printStatsPrivate(node->right);
    }
    if(node->left != NULL){
        printStatsPrivate(node->left);
    }
    //std::cout << node->value << ": " << getBalancePrivate(node) << std::endl;

    if(this->minValue > node->value)
        this->setMin(node->value);
    if(maxValue < node->value)
        this->setMax(node->value);
    this->setAverage(this->getAverage() + node->value);
    this->incrementNodeCount();

    if(node == root){
        this->setAverage(this->getAverage() / this->getNodeCount());
        std::cout << "min: " << this->getMin() << ", ";
        std::cout << "max: " << this->getMax() << ", ";
        std::cout << "avg: " << this->getAverage() << std::endl;
    }
}

/*
int Tree::getBalancePrivate(Node* node){
    if(root == NULL){
        return 0;
    }

    if(node->left != NULL)
        left = getBalancePrivate(node->left);
    if(node->right != NULL)
        right = getBalancePrivate(node->right);

    if(left < right)
        return left++;
    else
        return right++;
}

int Tree::getHeightPrivate(Node* node){
    if(node == NULL){
        return 0;
    }
}
*/


