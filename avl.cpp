#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

vector<int> int_vector(string array) // string array to int vector
{
  stringstream ss;
  vector<int> arr;
  ss << array;
  string temp; 
  int found; 
  while (!ss.eof()) 
  { 
    ss >> temp; 
    if (stringstream(temp) >> found) 
        arr.push_back(found);
    temp = ""; 
  }    
    return arr;
}

void delete_nodes(Node* root) // delete heaps at the end
{
  if(root != NULL)
  {
    delete_nodes(root->left);
    delete_nodes(root->right);
    delete root;
  }
}

Node* insert_master(Node* root, vector<int> int_vec)
{
    int rotations = 0;
    float N = int_vec.size();
    int visits = 0;
    int dummyvar;
    float n=0;
    for (int i = 0; i < N; i++) 
    {  
        if (lookup(root, int_vec[i], &dummyvar) != int_vec[i])
        {
          n +=1;
        }
        root = insert(root, int_vec[i], &rotations, &visits);
    }

    // Added 2 of 2 nodes.
    cout << "Added " << n << " of " << N << " nodes." << endl;
    // Visited 1 (0.5) nodes and performed 0 (0) rotations.
    cout << "Visited " << visits << " (" << visits/N << ") nodes and performed " << rotations << " (" << rotations/N << ") rotations.\n" << endl;


    return root;
}

void lookup_master(Node* root, vector<int> lookup_vec)
{
  int visits = 0;
  vector<int> found_vec;
  float N = lookup_vec.size();

  for (int i=0; i<N; i++)
  {
    int found = lookup(root, lookup_vec[i], &visits);
    if(lookup_vec[i] == found)
      found_vec.push_back(found);
  }

  // Found 3 of 5 nodes: [7, 12, 7]
  // Visited 10 (2) nodes and performed 0 (0) rotations.

  int n = found_vec.size();
  cout << "Found " << n << " of " << N << " nodes: [";

  for (int i=0; i<n; i++)
  {
    cout << found_vec[i];
    if(i<n-1)
      cout << ", ";
  }
  cout << "]\nVisited " << visits << " (" << visits/N << ") nodes and performed 0 (0) rotations.\n";
}


int main(int argc, char* argv[])
{
	// /root/avl-master/tests.left-left.avl
	if (argc > 1)
	{
		string line;
		ifstream inFile;
		inFile.open( argv[1] ); // note no mode needed 
    Node *root = NULL;
		if (!inFile)
		{
			cout<<"unable to open file";
		}
		while(getline(inFile, line))
		{
			if(line.length() > 6)
			{
				//cout << (line.substr(0,6)) << endl;
				string function_name = line.substr(0,6);
				if (function_name.compare("insert") == 0)
				{
					string array = line.substr(7, line.length());
          vector<int> int_vec = int_vector(array);
					root = insert_master(root, int_vec);
				}
        if (line.compare("print tree") == 0)
        {
          int c = 0;
          printTree(root, &c);
          cout << endl;
        }
        if (function_name.compare("lookup") == 0)
        {
          string array = line.substr(7, line.length());
          vector<int> lookup_vec = int_vector(array);
          lookup_master(root, lookup_vec);
          cout << endl;
        }
        if (line.compare("print left-left") == 0)
        {
          int upr = 2147483647;
          int lwr = -2147483648;
          vector< pair <int,int> > store;
          print_left_left(root, &upr, &lwr, &store);
          sort(store.begin(), store.end());
          int n = store.size();
          if (n>0)
          {
            cout << "The following inserts would cause a left-left rotation:" << endl;
            for (int i=0; i<n; i++)
            {
              if(store[i].first == store[i].second)
                cout << store[i].first;
              else
                cout << store[i].first << " to " << store[i].second;
              
              if(i<n-1)
                cout << ", ";
            }
            cout << endl;
          }
          else
          {
            cout << "No inserts would cause a left-left rotation." << endl;
          }
          cout << endl;
        }

        if (line.compare("print right-right") == 0)
        {
          int upr = 2147483647;
          int lwr = -2147483648;
          vector< pair <int,int> > store;
          print_right_right(root, &upr, &lwr, &store);
          sort(store.begin(), store.end());
          int n = store.size();
          if (n>0)
          {
            cout << "The following inserts would cause a right-right rotation:" << endl;
            for (int i=0; i<n; i++)
            {
              if(store[i].first == store[i].second)
                cout << store[i].first;
              else
                cout << store[i].first << " to " << store[i].second;
              
              if(i<n-1)
                cout << ", ";
            }
            cout << endl;
          }
          else
          {
            cout << "No inserts would cause a right-right rotation." << endl;
          }
          cout << endl;
        }

        if (line.compare("print left-right") == 0)
        {
          int upr = 2147483647;
          int lwr = -2147483648;
          vector< pair <int,int> > store;
          print_left_right(root, &upr, &lwr, &store);
          sort(store.begin(), store.end());
          int n = store.size();
          if (n>0)
          {
            cout << "The following inserts would cause a left-right rotation:" << endl;
            for (int i=0; i<n; i++)
            {
              if(store[i].first == store[i].second)
                cout << store[i].first;
              else
                cout << store[i].first << " to " << store[i].second;

              if(i<n-1)
                cout << ", ";
            }
            cout << endl;
          }
          else
          {
            cout << "No inserts would cause a left-right rotation." << endl;
          }
          cout << endl;
        } 

        if (line.compare("print right-left") == 0)
        {
          int upr = 2147483647;
          int lwr = -2147483648;
          vector< pair <int,int> > store;
          print_right_left(root, &upr, &lwr, &store);
          sort(store.begin(), store.end());
          int n = store.size();
          if (n>0)
          {
            cout << "The following inserts would cause a right-left rotation:" << endl;
            for (int i=0; i<n; i++)
            {
              if(store[i].first == store[i].second)
                cout << store[i].first;
              else
                cout << store[i].first << " to " << store[i].second;

              if(i<n-1)
                cout << ", ";
            }
            cout << endl;
          }
          else
          {
            cout << "No inserts would cause a right-left rotation." << endl;
          }
          cout << endl;
        }
			}
		}
    
    delete_nodes(root);
	}
	return 0;


}