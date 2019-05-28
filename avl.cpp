#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;

void insert_master(Node* root, vector<int> int_vec)
{

    // int str_length = str.length(); 
    int N = int_vec.size();

    int arr[N];
    copy(int_vec.begin(), int_vec.end(), arr);

    int j = sizeof(arr) / sizeof(arr[0]);
    // cout << j << endl;  
    removeDups(arr, j);

    int n = sizeof(arr) / sizeof(arr[0]);
    // cout << j << endl; 
    int rotations = 0;
    for (int i = 0; i <= n; i++) 
    {  
        insert(root, arr[i], rotations);
    } 

    cout << "Added " << n << " of " << j << " nodes." << endl;
    cout << "Visited " << j << " (1) nodes and performed " << rotations/n << " rotations" << endl;

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
                    vector<int> int_vec = int_vector(array);
					insert_master(root, int_vec);
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