#pragma once
#include <vector>
#include "LegoPiece.h"
#include "Node234.h"
#include <algorithm>

using namespace std;

template <typename T>
class BTree234
{
public:
	BTree234();
	BTree234(vector<T> keys);
	virtual ~BTree234();

	bool isEmpty();
	Node234<T> search(const T & key);
	Node234<T> search(const T & key, Node234<T> startNode);
	void addKey(const T & key);
	//void deleteKey(T key);

private:
	shared_ptr<Node234<T>> root;
	void findNodeToInsertKey(T key, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> parentNode);

};

template<typename T>
BTree234<T>::BTree234()
{
	this->root = make_shared<Node234<T>>(); 
}

template<typename T>
BTree234<T>::BTree234(vector<T> keys)
{
	try
	{
		this->root = new Node234<T>(keys);
	}
	catch (logic_error)
	{
		this->root = new Node234<T>();
		for (size_t i; i < keys.size(); i++)
			addKey(keys[i]);
	}

}

template<typename T>
BTree234<T>::~BTree234()
{
}

template<typename T>
bool BTree234<T>::isEmpty()
{
	return (this->root->getKeyCount() <= 0);
}

template<typename T>
Node234<T> BTree234<T>::search(const T & key)
{
	return search(key, this->root);
}

template<typename T>
Node234<T> BTree234<T>::search(const T & key, Node234<T> startNode)
{
	vector<T> keys = startNode.getKeys();
	if (find(keys.begin(), keys.end(), key) != keys.end())
		return startNode;
	if (startNode.getLeavesCount() <= 0)
		return nullptr;

	vector<T> compareKeys = vector<T>(key);
	compareKeys.push_back(startNode);
	compareKeys.sort(compareKeys.begin(), compareKeys.end());
	int leafPos = find(compareKeys.begin(), compareKeys.end(), key) - compareKeys.begin();
	return search(key, startNode.getLeafAt(leafPos));
}

template <typename T>
void BTree234<T>::addKey(const T & key)
{
	 findNodeToInsertKey(key, this->root, nullptr);

	/*if (!nodeToInsert->addKey(key))
	{
		throw logic_error("The key vector is full, not supposed to happen!\n");
	}*/

}

template<typename T>
void BTree234<T>::findNodeToInsertKey(T key, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> parentNode)
{

	if (startNode->getKeyCount() >= 3)
	{
		size_t medianPos = startNode->getMedianPos();
		shared_ptr<Node234<T>> leftNewNode(new Node234<T>());
		shared_ptr<Node234<T>> rightNewNode(new Node234<T>());

		//retrive keys value in the full node and push them in two separates node
		for (size_t i = 0; i < medianPos; i++)
			leftNewNode->addKey(startNode->getKeyAt(i));
		for (size_t i = medianPos + 1; i < startNode->getKeys().size(); i++)
			rightNewNode->addKey(startNode->getKeyAt(i));

		int leafPos = 0;

		if (!startNode->isLeaf())
		{
			for (size_t i = 0; i <= medianPos; i++)
				leftNewNode->pushLeaf(startNode->getLeafAt(i));
			for (size_t i = medianPos + 1; i < startNode->getLeaves().size(); i++)
				rightNewNode->pushLeaf(startNode->getLeafAt(i));

			//retrive old full node and erase it

		}
		
		if (startNode == this->root)
		{
			//create new root node with median key
			
			parentNode.reset(new Node234<T>());
			this->root = parentNode;
		}
		else
		{
			//retrive old full node and erase it
			leafPos = find(parentNode->getLeaves().begin(), parentNode->getLeaves().end(), startNode) - parentNode->getLeaves().begin();
			parentNode->removeLeaf(leafPos);
		}

		T medianKey = startNode->getKeyAt(medianPos);
		parentNode->addKey(medianKey);

		//add new nodes at the old node's position
		parentNode->insertLeafAt(leftNewNode, leafPos);
		parentNode->insertLeafAt(rightNewNode, leafPos + 1);

		startNode = parentNode;
	}

	if (startNode->isLeaf()) {
		if (!startNode->addKey(key))
			throw logic_error("The key vector is full, not supposed to happen!\n");
	} else
	{
		vector<T> sumKeys;
		sumKeys.push_back(key);
		sumKeys.reserve(sumKeys.size() + startNode->getKeys().size());
		sumKeys.insert(sumKeys.end(), startNode->getKeys().begin(), startNode->getKeys().end());
		sort(sumKeys.begin(), sumKeys.end());
		int leafPos = find(sumKeys.begin(), sumKeys.end(), key) - sumKeys.begin();
		findNodeToInsertKey(key, startNode->getLeafAt(leafPos), startNode);
	}
}


