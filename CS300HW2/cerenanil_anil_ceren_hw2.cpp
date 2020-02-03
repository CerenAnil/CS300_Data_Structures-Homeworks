#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <locale.h>
#include <stdlib.h>
#include <codecvt>
#include <windows.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <queue>
#include <utility> 
#include "binarySearchTree.h"

using namespace std;


void readFile(BinarySearchTree<translation> & bst)
{
	//for reading the UTF8
	_setmode(_fileno(stdout), _O_U8TEXT);
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	wifstream wif("dictUpdated.txt");
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	wstringstream wss;
	wss << wif.rdbuf();
	wstring str = wss.str();
	wstring line;
	int cnt = 0;
	//read line by line from file
	while (str.length() != 0)
	{
		if (str.substr(0,1) != L"\n")
		{
			if(str.substr(0,1) != L"\r")
				line += str.substr(0,1);
			str = str.substr(1);
		}
		else
		{
			//split the word and meaning
			str = str.substr(1);
			if(line == L"")
				continue;
			wstring word, meaning;
			wstringstream wss2(line);
			wss2 >> word >> meaning;
			//wcout << word << L" ---> " << meaning << endl;
			line = L"";

			translation* input = new translation;
			input->mainWord = word;
			input->definition = meaning;
			bst.insert(*input);
		}

	}
}
void help()
{
	wcout << "***Help***\nQuery: 1\nAdd new transition: 2\nAdd new word: 3\nExit:0\n";
}
int main()
{
	translation * ITEM_NOT_FOUND = new translation;;
	ITEM_NOT_FOUND->definition = L"";
	ITEM_NOT_FOUND->mainWord = L"";
    BinarySearchTree<translation> bst( *ITEM_NOT_FOUND );
	readFile(bst);
	help();
	wstring command = L"";
	wstring queriedWord, newMeaning,newWord;
	bst.printTree();
 

	while(command != L"0")
	{
		wcout <<"Enter Command: ";
		wcin >> command;

		if(command == L"1") //Show translation
		{
			wcout << "Enter queried word:";
			wcin >> queriedWord;
			translation temp = bst.find(queriedWord);
			if(temp.mainWord != ITEM_NOT_FOUND->mainWord)
				wcout << temp.mainWord << L" ---> " << temp.definition << endl;
		}
		else if(command == L"2") //Add new translation
		{
			wcout << "Enter queried word:";
			wcin >> queriedWord;
			
			wstring find = bst.find(queriedWord).mainWord;
			if(find == ITEM_NOT_FOUND->mainWord)
			{

				wcout << "Word does not exist." << endl;
			}
			else
			{
				wcout << "Enter the new translation: ";
				wcin >> newMeaning;
				bst.findAndChange(queriedWord,newMeaning);

				wcout << L"***UPDATED***" << endl;
			}


			
		}
		else if(command == L"3") //Add new word
		{
			wcout << "Enter New Word:";
			wcin >> newWord;

			translation temp = bst.find(newWord);
			if(temp.mainWord != ITEM_NOT_FOUND->mainWord)
			{
				wcout << L"Word already exists, if you want to add new translation please use command 2." << endl;
			}
			else
			{
				wcout << "Enter Translation:";
				wcin >> newMeaning;
				translation* input = new translation;
				input->mainWord = newWord;
				input->definition = newMeaning;
				bst.insert(*input);
			}
		}

	}

	wcout << "Bye...\n";
	return 0;
}