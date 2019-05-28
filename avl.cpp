#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

vector<int> removeDups(vector<int> a, int N)
{
    set<int> s;
    for(int i = 0; i < N; ++i ) s.insert(a[i]);
    a.assign( s.begin(), s.end() );
    return a;
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

void insert_master(vector<int> int_vec)
{

    // int N = int_vec.size(); // Original size
    
    //int_vec = removeDups(int_vec, N);
    int n = int_vec.size();

    // int arr[n];
    // copy(int_vec.begin(), int_vec.end(), arr);

    Node *root = NULL;

    // int rotations = 0;
    for (int i = 0; i < n; i++) 
    {  
        root = insert(root, int_vec[i]);
    } 
    // cout << "Added " << n << " of " << N << " nodes." << endl;
    // cout << "\nVisited " << N << " (1) nodes and performed " << " rotations" << endl;

    preOrder(root);
    cout << endl;

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
			if(line.length() > 6)
			{
				//cout << (line.substr(0,6)) << endl;
				string function_name = line.substr(0,6);
				if (function_name.compare("insert") == 0)
				{
					string array = line.substr(7, line.length());
                    vector<int> int_vec = int_vector(array);
					insert_master(int_vec);
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