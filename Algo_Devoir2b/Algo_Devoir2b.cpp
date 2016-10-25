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

vector<vector<string>> readLegoFile(string fileName)
{
	vector<vector<string>> data;
	ifstream infile(fileName);
	string dummyLine;
	getline(infile, dummyLine);
	getline(infile, dummyLine);

	while (infile)
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

		if(!record.empty()) data.push_back(record);
		
	}
	return data;
}

int main()
{
	string fileName = "lego_pieces2.txt";
	vector<vector<string>> data = readLegoFile(fileName);
	vector<LegoPiece> piecesList;

	BTree234<LegoPiece> tree;

	for(size_t i = 0; i < data.size(); i++)
	{
		LegoPiece piece = LegoPiece(data[i][0], data[i][1], data[i][2]);
		piecesList.push_back(piece);
		tree.addKey(piece);
	}
	
	shared_ptr<Node234<LegoPiece>> node  = tree.search(piecesList[5]);
	//tree.deleteKey(piecesList[0]);
	cout << tree << endl;
	RBTree<LegoPiece> rbTree = RBTree<LegoPiece>::convertToRBTree(tree);
	BTree234<LegoPiece> tree2 = BTree234<LegoPiece>::convertToBTree234(rbTree);
	
	system("pause");
	return 0;
}


