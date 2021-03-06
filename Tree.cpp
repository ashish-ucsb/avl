#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  

int max(int a, int b)  
{  
    return (a > b)? a : b;  
} 

Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; 
    return(node);  
}  
  
 
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  

Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
  

Node* insert(Node* node, int key, int *rotations, int *visits)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)
    {
        *visits += 1;  
        node->left = insert(node->left, key, rotations, visits);  
    }
    else if (key > node->key)
    {
        *visits += 1;  
        node->right = insert(node->right, key, rotations, visits); 
    } 
    else // Equal keys are not allowed in BST  
    {
        *visits += 1;
        return node;
    }  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)
    {
        *rotations+=1;
        return rightRotate(node);
    }  
          
    // Right Right Case  
    if (balance < -1 && key > node->right->key)
    {
        *rotations+=1;
        return leftRotate(node);
    }  
          
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        *rotations+=2;
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        *rotations+=2;
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}  

int lookup(Node* root, int find, int *visits)
{
    if(root != NULL)
    {
        if(find == root->key)
        {
            *visits +=1;
            return find;
        }
        else if(find < root->key)
        {
            *visits +=1;
            return lookup(root->left, find, visits);
        }
        else if(find > root->key)
        {
            *visits +=1;
            return lookup(root->right, find, visits);
        }
        else
        {
            return -1;
        }
    }
    else
        return -1;
}

void printTree(Node* root, int *c)
{
    if(root != NULL)
    {
        if (root->left != NULL || root->right != NULL)
        {
            cout << string(*c*2, ' ' );
            cout << "Node(" << root->key << ", h=" << root->height -1 << "):" << endl;
            int s= *c+1;
            printTree(root->left, &s);
            printTree(root->right, &s);
        }
        if (root->left == NULL && root->right == NULL)
        {
            cout << string(*c*2, ' ' );
            cout << "Leaf(" << root->key << ")" << endl;
        }
    }
    else
    {
        cout << string(*c*2, ' ' );
        cout << "Null" << endl;
    }
}

void print_left_left(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store)
{
    if(root != NULL)
    {
        int prebal = getBalance(root);
        if(prebal == -1)
            *lwr = root->key + 1;
        if(prebal == 1 && root->left != NULL && root->left->left == NULL)
        {
            *upr = root->left->key - 1;
            store->push_back(make_pair(*lwr, *upr));
            *upr = 2147483647;
            *lwr = -2147483648;
        }
        print_left_left(root->left, upr, lwr, store);
        print_left_left(root->right, upr, lwr, store);
    }
}

void print_right_right(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store)
{
    if (root != NULL)
    {
        int prebal = getBalance(root);
        if(prebal == 1)
            *upr = root->key - 1;
        if(prebal == -1 && root->right != NULL && root->right->right == NULL)
        {
            *lwr = root->right->key + 1;
            store->push_back(make_pair(*lwr, *upr));
            *upr = 2147483647;
            *lwr = -2147483648;
        }
        print_right_right(root->left, upr, lwr, store);
        print_right_right(root->right, upr, lwr, store);
    }
}

void print_left_right(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store)
{
    if (root != NULL)
    {
        int prebal = getBalance(root);
        if(prebal == 1 && root->left != NULL && root->left->right == NULL)
        {
            *upr = root->key - 1;
            *lwr = root->left->key + 1;
            store->push_back(make_pair(*lwr, *upr));
            *upr = 2147483647;
            *lwr = -2147483648;
        }
        print_left_right(root->left, upr, lwr, store);
        print_left_right(root->right, upr, lwr, store);
    }
}

void print_right_left(Node* root, int *upr, int *lwr, vector< pair <int,int> > *store)
{
    if (root != NULL)
    {
        int prebal = getBalance(root);
        if(prebal == -1 && root->right != NULL && root->right->left == NULL)
        {
            *lwr = root->key +1;
            *upr = root->right->key -1;
            store->push_back(make_pair(*lwr, *upr));
            *upr = 2147483647;
            *lwr = -2147483648;
        }
        print_right_left(root->left, upr, lwr, store);
        print_right_left(root->right, upr, lwr, store);
    }
}