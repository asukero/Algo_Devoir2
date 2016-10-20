#pragma once
#include <vector>
#include "LegoPiece.h"

using namespace std;

template <typename T>
class BTree234
{
public:
	BTree234();
	BTree234(vector<LegoPiece> legoPieces);
	virtual ~BTree234();

	T findKey(T Key);
	void addKey(T Key);
	void deleteKey(T Key);

};
