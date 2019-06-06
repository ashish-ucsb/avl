#ifndef TREE_H
#define TREE_H
using namespace std;

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
Node* insert(Node* node, int key, int *rotations, int *visits);
int lookup(Node* root, int find, int *visits);

void printTree(Node* root, int *c);
void print_left_left(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store);
void print_right_right(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store);
void print_left_right(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store);
void print_right_left(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store);

#endif

