#include <iostream>
#include <string>
#include "header.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <cmath>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

using namespace std;

void output(vector<translation> arr, string fileName){
	ofstream myFile;
	myFile.open(fileName);
	for (unsigned int i = 0; i < arr.size(); i++) {
		myFile << arr[i].mainWord << "	" ;
		myFile << arr[i].definition << endl;
	}
	myFile.close();
}

void bstFunc(BinarySearchTree<translation> & bst)
{
	ifstream inp("dict.txt");
	stringstream ss;
	string str = ss.str();
	string line;
	while(getline(inp,line))
	{
		if(line == "")
			continue;
		istringstream iss(line);
		string word, meaning;
		iss >> word >> meaning;
		translation input ;
		input.mainWord = word;
		input.definition = meaning;
		bst.insert(input);

	}
}

void hashFunc(HashTable<translation> & ht)
{
	ifstream inp("dict.txt");
	stringstream ss;
	string str = ss.str();
	string line;
	while(getline(inp,line))
	{
		if(line == "")
			continue;
		istringstream iss(line);
		string word, meaning;
		iss >> word >> meaning;
		translation input ;
		input.mainWord = word;
		input.definition = meaning;
		ht.insert(input);

	}
}

double bstQuery(vector<translation> & arrBST, BinarySearchTree<translation> & bst ,int numIter)
{

	string str;
	ifstream iss2("query1.txt");
	while (getline(iss2, str))
	{
		translation temp;
		temp.mainWord = str;
		arrBST.push_back(temp);
	}

	auto startBST = chrono::high_resolution_clock::now();
	for (int i = 0; i <= numIter; i++)
	{
		for(int k = 0; k < pow(2,i); k++)
		{
			for(unsigned int i = 0; i < arrBST.size(); i++)
			{
				string bstfind = bst.find(arrBST[i].mainWord).definition;
				arrBST[i].definition=bstfind;
			}
		}
	}
	auto timeBST = chrono::high_resolution_clock::now();
	auto diffBST = timeBST - startBST;
	double time = chrono::duration<double, nano>(diffBST).count();
	return time;
}

double htQuery(vector<translation> & arrHT, HashTable<translation> & ht, int numIter)
{
	string str;
	ifstream iss("query1.txt");
	while (getline(iss, str))
	{
		translation temp;
		istringstream ssi(str);
		string tempstr;
		ssi >>tempstr;
		temp.mainWord = tempstr;
		arrHT.push_back(temp);
	}
	auto startHT = chrono::high_resolution_clock::now();
	for (int i = 0; i <= numIter; i++)
	{
		for(int k = 0; k < pow(2,i); k++)
		{

			for(unsigned int i = 0; i < arrHT.size(); i++)
			{
				string htfind = ht.find(arrHT[i]).definition;
				arrHT[i].definition= htfind;
			}
		}
	}
	auto timeHT = chrono::high_resolution_clock::now();
	auto diffHT = timeHT - startHT;
	double time = chrono::duration<double, nano>(diffHT).count();
	return time;
}

int main()
{
	//CODE FOR BINARY SEARCH TREE
	translation * ITEM_NOT_FOUND = new translation;;
	ITEM_NOT_FOUND->definition = "";
	ITEM_NOT_FOUND->mainWord = "";
	BinarySearchTree<translation> bst( *ITEM_NOT_FOUND );
	cout << "Building a binary tree for dict.txt..." << endl;
	bstFunc(bst);
	//CODE FOR BINARY SEARCH TREE

	//CODE FOR HASH TABLE
	translation ITEM_NOT_FOUND2;
	ITEM_NOT_FOUND2.definition = "";
	ITEM_NOT_FOUND2.mainWord = "abcd";
	HashTable<translation> ht(ITEM_NOT_FOUND2);
	cout << "Building a hash table for dict.txt..." << endl;
	hashFunc(ht);
	cout << "After preprocessing, the unique word count is " << ht.currentSize << ". Current load ratio is " << double(ht.currentSize)/double(ht.array.size()) << endl;

	//CODE FOR HASH TABLE

	//QUERIES
	cout << "Running queries in query1.txt..." << endl << endl;
	vector<translation> arrHT, arrBST;

	double bstQueryTime= bstQuery(arrBST,bst,0);
	double htQueryTime = htQuery(arrHT, ht,0);

	output(arrHT, "ht_results.txt");
	output(arrBST, "bst_results.txt");
	//QUERIES

	cout << "***********************************************" << endl;
	cout << "Benchmark results for Binary Search Tree (BST):" << endl;
	cout << "***********************************************" << endl;
	cout << "+ Elapsed time: " << bstQueryTime << " ns" << endl;
	cout << "+ Average query time: " << double(bstQueryTime/ht.currentSize ) << " ns" << endl << endl;

	cout << "***********************************************" << endl;
	cout << "Benchmark results for Hash Table:" << endl;
	cout << "***********************************************" << endl;
	cout << "+ Elapsed time: " << htQueryTime << " ns" << endl;
	cout << "+ Average query time: " << double(htQueryTime/ht.currentSize) << " ns" << endl;
	cout << "+ Speed up: " << double(bstQueryTime/ht.currentSize ) / double(htQueryTime/ht.currentSize) << " x" << endl << endl;

	cout << "Time measurements in ns (N, 4096N):" << endl;
	cout << "*****************************" << endl;

	cout << "bst" << endl;
	cout << "N			time" << endl;
	cout << "1			" << bstQuery(arrBST,bst,0) << endl;
	cout << "2			" << bstQuery(arrBST,bst,1) << endl;
	cout << "4			" << bstQuery(arrBST,bst,2) << endl;
	cout << "8			" << bstQuery(arrBST,bst,3) << endl;
	cout << "16			" << bstQuery(arrBST,bst,4) << endl;
	cout << "32			" << bstQuery(arrBST,bst,5) << endl;
	cout << "64			" << bstQuery(arrBST,bst,6) << endl;
	cout << "128			" << bstQuery(arrBST,bst,7) << endl;
	cout << "256			" << bstQuery(arrBST,bst,8) << endl;
	cout << "512			" << bstQuery(arrBST,bst,9) << endl;
	cout << "1024			" << bstQuery(arrBST,bst,10) << endl;
	cout << "2048			" << bstQuery(arrBST,bst,11) << endl;
	cout << "4096			" << bstQuery(arrBST,bst,12) << endl;


	cout << "ht" << endl;
	cout << "N			time" << endl;
	cout << "1			" << htQuery(arrHT,ht,0) << endl;
	cout << "2			" << htQuery(arrHT,ht,1) << endl;
	cout << "4			" << htQuery(arrHT,ht,2) << endl;
	cout << "8			" << htQuery(arrHT,ht,3) << endl;
	cout << "16			" << htQuery(arrHT,ht,4) << endl;
	cout << "32			" << htQuery(arrHT,ht,5) << endl;
	cout << "64			" << htQuery(arrHT,ht,6) << endl;
	cout << "128			" << htQuery(arrHT,ht,7) << endl;
	cout << "256			" << htQuery(arrHT,ht,8) << endl;
	cout << "512			" << htQuery(arrHT,ht,9) << endl;
	cout << "1024			" << htQuery(arrHT,ht,10) << endl;
	cout << "2048			" << htQuery(arrHT,ht,11) << endl;
	cout << "4096			" << htQuery(arrHT,ht,12) << endl;





	return 0;
}
