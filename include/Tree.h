#ifndef TREE_H
#define TREE_H

class Tree
{
    private:
        typedef struct node{
            int value;
            struct node* left;
            struct node* right;
        }Node;

        Node* root;
        int minValue, maxValue, nodeCount;
        float average;
        bool isAVL;

        void incrementNodeCount();
        void addNodePrivate(int value, Node* node);
        void printStatsPrivate(Node* node);
        int getBalancePrivate(Node* node, int &height);

        void setColor(int i);

    public:
        Tree();
        ~Tree();

        Node* createNode(int value);
        void addNode(int value);
        void printStats();
        bool searchNode(Node* nodeSearch, Node* nodeSubtree);
        bool searchSubtree(Node *nodeSearch, Node* nodeSubtree);

        void setRoot(Node* root);
        Node* getRoot() const;
        void setMin(int minValue);
        int getMin() const;
        void setMax(int maxValue);
        int getMax() const;
        void setNodeCount(int nodeCount);
        int getNodeCount() const;
        void setAverage(float average);
        float getAverage() const;
        void setIsAVL(bool value);
        bool getIsAVL() const;
};

#endif // TREE_H
