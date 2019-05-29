#ifndef TREE_H
#define TREE_H

class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right; 
    int height;

};

int height(Node *N);
int max(int a, int b);
Node* newNode(int key);
Node* rightRotate(Node *y);
Node* leftRotate(Node *x);
int getBalance(Node *N);
Node* insert(Node* node, int key, int *rotationsPointer);
void preOrder(Node *root);

#endif
