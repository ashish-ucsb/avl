// #include "Tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.cpp"
using namespace std;

#include "Tree.h"

class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right; 
    int height;

};

// A utility function to get the  
// height of the tree  
int height1(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  
// A utility function to get maximum 
// of two integers  
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
/* Helper function that allocates a  
   new node with the given key and  
   NULL left and right pointers. */
Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node* rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height1(y->left), 
                    height1(y->right)) + 1;  
    x->height = max(height1(x->left), 
                    height1(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node* leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height1(x->left),     
                    height1(x->right)) + 1;  
    y->height = max(height1(y->left),  
                    height1(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height1(N->left) - height1(N->right);  
}  

// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
Node* insert(Node* node, int key, int &rotations)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key, rotations);  
    else if (key > node->key)  
        node->right = insert(node->right, key, rotations);  
    else // Equal keys are not allowed in BST  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height1(node->left),  
                        height1(node->right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)
    {
    	return rightRotate(node);
    	rotations += 1;
    }  
         
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key) 
    {
    	return leftRotate(node);
    	rotations += 1;
    }
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);
        rotations += 2;  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);
        rotations += 2;  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}

void removeDups(int arr[], int n) 
{ 
    // Hash map which will store the 
    // elements which has appeared previously. 
    unordered_map<int, bool> mp; 
  
    for (int i = 0; i < n; ++i) { 
  
        // Print the element if it is 
        // there in the hash map   
        // Insert the element in the hash map 
        mp[arr[i]] = true; 
    } 
}

void insert_master(Node* root, string str)
{

    int str_length = str.length(); 

    int arr[str_length] = { 0 };
    int j = 0, i;
  
    for (i = 0; str[i] != '\0'; i++) 
    { 
        if (str[i] == ' ') 
        {  
            j++; 
        } 
        else { 
            arr[j] = arr[j] * 10 + (str[i] - 48); 
        } 
    } 
    j = sizeof(arr) / sizeof(arr[0]);
    // cout << j << endl;  
    removeDups(arr, j);

    int n = sizeof(arr) / sizeof(arr[0]);
    // cout << j << endl; 
    int rotations = 0;
    for (i = 0; i <= n; i++) 
    {  
        insert(root, arr[i], rotations);
    } 

    cout << "Added " << n << " of " << j << " nodes." << endl;
    cout << "Visited " << j << " (1) nodes and performed " << rotations/n << " rotations" << endl;

}

int main(int argc, char* argv[])
{
	// /root/avl-master/tests.left-left.avl
	if (argc > 1)
	{
		string line;
		ifstream inFile;
		inFile.open( argv[1] ); // note no mode needed 
		if (!inFile)
		{
			cout<<"unable to open file";
		}
		while(getline(inFile, line))
		{
			Node *root = NULL;
			if(line.length() > 6)
			{
				//cout << (line.substr(0,6)) << endl;
				string function_name = line.substr(0,6);
				if (function_name.compare("insert") == 0)
				{
					string array = line.substr(7, line.length());
					insert_master(root, array);
				}
			}
			
			// if (function_name == "insert")
			// {
			// 	string num_array = line[1:];
			// 	cout << num_array <<endl;
			// }
		}
	}
	return 0;


}