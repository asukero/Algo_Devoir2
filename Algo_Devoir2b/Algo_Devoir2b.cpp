// Algo_Devoir2b.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "LegoPiece.h"
#include "BTree234.h"
#include "RBTree.h"
#include <iostream>

using namespace std;

vector<vector<string>> readLegoFile(string fileName, int maxLines)
{
	vector<vector<string>> data;
	ifstream infile(fileName);
	string dummyLine;

	//skipping first two lines
	getline(infile, dummyLine);
	getline(infile, dummyLine);
	int numLines = 0;

	while (infile && numLines < maxLines)
	{
		string s;
		if (!getline(infile, s)) break;

		istringstream ss(s);
		vector <string> record;

		string line;
		while (getline(ss, line))
		{

			size_t prev = 0, pos;
			char delimiter = ',';
			while ((pos = line.find_first_of(delimiter, prev)) != string::npos)
			{
				if (pos > prev)
					record.push_back(line.substr(prev, pos - prev));
				if (line[pos + 1] == '"' || prev == pos)
					delimiter = '"';
				else
					delimiter = ',';
				prev = pos + 1;
			}
			if (prev < line.length())
				record.push_back(line.substr(prev, string::npos));
		}

		if (!record.empty()) data.push_back(record);
		numLines++;
	}
	return data;
}

void searchAndDelete(vector<LegoPiece> piecesList, BTree234<LegoPiece> tree)
{
	cout << "Pleaser enter a piece id to search the node who stores it in the tree" << endl;
	string searchInput;
	cin >> searchInput;

	int keyPos = find(piecesList.begin(), piecesList.end(), searchInput) - piecesList.begin();
	while (keyPos == piecesList.size())
	{
		cout << "Error: the piece you were searching was not read from the text file in the first place." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> searchInput;
	}

	cout << "Searching for the piece with id " << searchInput << "..." << endl;
	LegoPiece key = piecesList[keyPos];
	shared_ptr<Node234<LegoPiece>> node = tree.search(key);

	if (node != nullptr)
	{
		cout << "The node was found !" << endl;
		cout << *(node) << endl;
		cout << endl;
		cout << "Do you want to delete that key ? [y/n]" << endl;

		char answer;
		cin >> answer;
		while (cin.fail() || answer != 'y' && answer != 'n')
		{
			cout << "Please enter a valid answer" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> answer;
		}

		if (answer == 'y')
		{
			cout << "Deleting key...";
			tree.deleteKey(key);
			cout << "Done." << endl;
			cout << tree << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "The node was not found" << endl;
		searchAndDelete(piecesList, tree);

	}
}

int main()
{
	string fileName = "lego_pieces.txt";
	
	int numberInput;
	cout << "Please enter a number of line you want to read from " << fileName << endl;
	cin >> numberInput;

	while (cin.fail() || numberInput <= 0)
	{
		cout << "Error: the value entered is not a positive integer" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> numberInput;
	}

	cout << "Reading " << numberInput << " lines from " << fileName << "..." << endl;
	vector<vector<string>> data = readLegoFile(fileName, numberInput);
	vector<LegoPiece> piecesList;

	cout << "Generating BTree 234...";
	BTree234<LegoPiece> tree;
	for (size_t i = 0; i < data.size(); i++)
	{
		LegoPiece piece = LegoPiece(data[i][0], data[i][1], data[i][2]);
		piecesList.push_back(piece);
		tree.addKey(piece);
	}
	cout << " Done." << endl;
	cout << tree << endl;
	cout << endl;

	searchAndDelete(piecesList, tree);

	cout << "Convert BTree234 to RBTree...";
	RBTree<LegoPiece> rbTree = RBTree<LegoPiece>::convertToRBTree(tree);
	cout << "Done." << endl;
	cout << rbTree << endl;
	cout << endl;

	cout << "Do you want to convert it back? [y/n]" << endl;
	char answer;
	cin >> answer;
	while (cin.fail() || answer != 'y' && answer != 'n')
	{
		cout << "Please enter a valid answer" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> answer;
	}

	if (answer == 'y')
	{
		cout << "Convert RBTree to BTree234...";
		BTree234<LegoPiece> tree2 = BTree234<LegoPiece>::convertToBTree234(rbTree);
		cout << "Done." << endl;
		cout << tree2 << endl;
		cout << endl;
	}



	system("pause");
	return 0;
}


