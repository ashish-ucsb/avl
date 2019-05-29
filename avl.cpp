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

vector<int> int_vector(string array)
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

Node* insert_master(vector<int> int_vec, Node* root)
{
    int rotations = 0;
    int N = int_vec.size();
    // int n = removeDups(int_vec, N);
    for (int i = 0; i < N; i++) 
    {  
        root = insert(root, int_vec[i], &rotations);
    }
    //Added 2 of 2 nodes.
    // cout << "Added " << n << " of " << N << " nodes." << endl;
    //Visited 1 (0.5) nodes and performed 0 (0) rotations.
    // cout << "performed " << rotations << " (0) rotations" << endl;

    return root;

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
					root = insert_master(int_vec, root);
				}
        if (line.compare("print tree") == 0)
        {
          preOrder(root);
          cout << endl;
        }
			}
		}
        
	}
	return 0;


}