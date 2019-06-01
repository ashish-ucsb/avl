#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

int removeDups(vector<int> a, int N)
{
    set<int> s;
    for(int i = 0; i < N; ++i ) s.insert(a[i]);
    a.assign( s.begin(), s.end() );
    return a.size();
}

vector<int> int_vector(string array) // string array to int vector
{
  stringstream ss;
  vector<int> arr;
  ss << array;
  string temp; 
  int found; 
  while (!ss.eof()) 
  { 
  
        /* extracting word by word from stream */
        ss >> temp; 
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found) 
            arr.push_back(found);
  
        /* To save from space at the end of string */
        temp = ""; 
    }    
    return arr;
}

Node* insert_master(Node* root, vector<int> int_vec)
{
    int rotations = 0;
    int N = int_vec.size();
    int visits = 0;
    int n = removeDups(int_vec, N);
    for (int i = 0; i < N; i++) 
    {  
        root = insert(root, int_vec[i], &rotations, &visits);
    }

    // Added 2 of 2 nodes.
    cout << "Added " << n << " of " << N << " nodes." << endl;
    // Visited 1 (0.5) nodes and performed 0 (0) rotations.
    cout << "Visited " << visits << " (" << visits/N << ") nodes and performed " << rotations << " (" << rotations << ") rotations.\n" << endl;

    return root;
}

void lookup_master(Node* root, vector<int> lookup_vec)
{
  vector<int> tree_vec;
  lookup(root, tree_vec);
  vector<int> found_vec;
  int count = 0;

  int n=lookup_vec.size();
  for (int i=0; i<n; i++)
  {
    vector<int>::iterator it;
    it = find(tree_vec.begin(), tree_vec.end(), lookup_vec[i]);
    if (it != tree_vec.end())
    {
      found_vec.push_back(lookup_vec[i]);
      count +=1;
    }
  }
  int p=found_vec.size();
  cout << "Found " << count << " of " << n << " nodes: [";
  for (int i=0; i<p; i++)
  {
    cout << found_vec[i];
    if(i<p-1)
    {
      cout << ", ";
    } 
  }
  cout << "]" << endl;
  // Found 3 of 5 nodes: [7, 12, 7]
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
    int upr = 2147483647;
    int lwr = -2147483647;
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
          print_left_left(root, &upr, &lwr);
          cout << "The following inserts would cause a left-left rotation:" << "\n" << lwr << " to " << upr << "\n" << endl;
        }
        if (line.compare("print right-right") == 0)
        {
          print_right_right(root, &upr, &lwr);
          cout << "The following inserts would cause a right-right rotation:" << "\n" << lwr << " to " << upr << "\n" << endl;
        }
        if (line.compare("print left-right") == 0)
        {
          cout << "Print LEFT-RIGHT" << endl;
        } 
        if (line.compare("print right-left") == 0)
        {
          cout << "Print RIGHT-LEFT" << endl;
        }
			}
		}
        
	}
	return 0;


}