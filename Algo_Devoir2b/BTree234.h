#pragma once
#include <vector>
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
	shared_ptr<Node234<T>> search(const T & key);
	void addKey(const T & key);

	void deleteKey(const T & keyToDelete);

private:
	shared_ptr<Node234<T>> root;
	void _addKey(T key, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> parentNode);
	void _deleteKey(const T& keyToDelete, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> nodeToDelete);
	shared_ptr<Node234<T>> _search(const T & key, shared_ptr<Node234<T>> startNode);

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
		this->root = make_shared<Node234<T>>(keys);
	}
	catch (logic_error)
	{
		this->root = make_shared<Node234<T>>();
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
shared_ptr<Node234<T>> BTree234<T>::search(const T & key)
{
	return _search(key, this->root);
}

template<typename T>
shared_ptr<Node234<T>> BTree234<T>::_search(const T & key, shared_ptr<Node234<T>> startNode)
{
	vector<T> keys = startNode->getKeys();
	if (find(keys.begin(), keys.end(), key) != keys.end())
		return startNode;
	if (startNode->isLeaf())
		return nullptr;

	vector<T> compareKeys;
	compareKeys.push_back(key);
	compareKeys.reserve(compareKeys.size() + startNode->getKeys().size());
	compareKeys.insert(compareKeys.end(), startNode->getKeys().begin(), startNode->getKeys().end());
	sort(compareKeys.begin(), compareKeys.end());
	int leafPos = find(compareKeys.begin(), compareKeys.end(), key) - compareKeys.begin();
	return _search(key, startNode->getLeafAt(leafPos));
}

template <typename T>
void BTree234<T>::addKey(const T & key)
{
	_addKey(key, this->root, nullptr);
}

template<typename T>
void BTree234<T>::deleteKey(const T & keyToDelete)
{
	_deleteKey(keyToDelete, this->root, nullptr);
}

template<typename T>
void BTree234<T>::_deleteKey(const T & keyToDelete, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> nodeToDelete)
{
	int keyPosition = find(startNode->getKeys().begin(), startNode->getKeys().end(), keyToDelete) - startNode->getKeys().begin();

	if (keyPosition != startNode->getKeyCount())
		nodeToDelete = startNode;

	if (startNode->isLeaf())
	{
		if (startNode == nodeToDelete)
		{
			if (keyPosition != startNode->getKeyCount())
			{
				startNode->removeKey(keyPosition);
				return;
			}
		}
		if (nodeToDelete != nullptr)
		{
			keyPosition = find(nodeToDelete->getKeys().begin(), nodeToDelete->getKeys().end(), keyToDelete) - nodeToDelete->getKeys().begin();
			if (keyPosition != nodeToDelete->getKeyCount())
				nodeToDelete->removeKey(keyPosition);
			nodeToDelete->addKey(startNode->getKeyAt(0));
			startNode->removeKey(0);
			return;

		}
		throw logic_error("key not found in the tree!\n");

	}
	shared_ptr<Node234<T>> leftNeighborNode;
	shared_ptr<Node234<T>> rightNeighborNode;
	shared_ptr<Node234<T>> mergedNode;
	shared_ptr<Node234<T>> nextNode;

	int nextLeafPos;
	if (nodeToDelete == nullptr)
	{
		//search next node to visit
		vector<T> sumKeys;
		sumKeys.push_back(keyToDelete);
		sumKeys.reserve(sumKeys.size() + startNode->getKeys().size());
		sumKeys.insert(sumKeys.end(), startNode->getKeys().begin(), startNode->getKeys().end());
		sort(sumKeys.begin(), sumKeys.end());
		nextLeafPos = find(sumKeys.begin(), sumKeys.end(), keyToDelete) - sumKeys.begin();
		nextNode = startNode->getLeafAt(nextLeafPos);
	}
	else
	{
		//search next node to visit
		vector<T> sumKeys;
		sumKeys.push_back(keyToDelete);
		sumKeys.reserve(sumKeys.size() + startNode->getKeys().size());
		sumKeys.insert(sumKeys.end(), startNode->getKeys().begin(), startNode->getKeys().end());
		sort(sumKeys.begin(), sumKeys.end());
		nextLeafPos = find(sumKeys.begin(), sumKeys.end(), keyToDelete) - sumKeys.begin() +1;
		nextNode = startNode->getLeafAt(nextLeafPos);
	}


	if (nextNode->getKeyCount() == 1)
	{
		if (nextLeafPos > 0)
			leftNeighborNode = startNode->getLeafAt(nextLeafPos - 1);
		if (nextLeafPos < startNode->getLeavesCount() - 1)
			rightNeighborNode = startNode->getLeafAt(nextLeafPos + 1);

		if (leftNeighborNode != nullptr && leftNeighborNode->getKeyCount() != 1)
		{
			mergedNode = leftNeighborNode;
			nextNode->addKey(startNode->getKeyAt(nextLeafPos - 1));
			if (!mergedNode->isLeaf())
			{
				nextNode->pushLeaf(mergedNode->getLeafAt(mergedNode->getLeavesCount() - 1));
				mergedNode->removeLeaf(mergedNode->getLeavesCount() - 1);
			}

			startNode->removeKey(nextLeafPos - 1);
			startNode->addKey( mergedNode->getKeyAt(mergedNode->getLeavesCount() - 1));
			mergedNode->removeKey(mergedNode->getLeavesCount() - 1);
		}
		else if (rightNeighborNode != nullptr && rightNeighborNode->getLeavesCount() != 1)
		{
			mergedNode = rightNeighborNode;
			nextNode->addKey(startNode->getKeyAt(nextLeafPos));
			if (!mergedNode->isLeaf())
			{
				nextNode->pushLeaf(mergedNode->getLeafAt(0));
				mergedNode->removeLeaf(0);
			}

			startNode->removeKey(nextLeafPos);
			startNode->addKey(mergedNode->getKeyAt(0));
			mergedNode->removeKey(0);
		}
		else
		{
			//if it can't get a key from left or right neighbors then it will merge with one of them and get a key from the parent node
			if (true)
			{
				mergedNode = make_shared<Node234<T>>();

				//merge nextnode and left neighboor with parent key
				if (leftNeighborNode != nullptr)
				{
					//adds nextNode leaves to merged node
					if (!nextNode->isLeaf())
					{
						for (size_t i = 0; i < leftNeighborNode->getLeavesCount(); i++)
							mergedNode->pushLeaf(leftNeighborNode->getLeafAt(i));
						for (size_t i = 0; i < nextNode->getLeavesCount(); i++)
							mergedNode->pushLeaf(nextNode->getLeafAt(i));
					}

					//adds left neighboor only key, left key of the parent node and next node only key to the merged node
					mergedNode->addKey(leftNeighborNode->getKeyAt(0));
					mergedNode->addKey(startNode->getKeyAt(nextLeafPos - 1));
					mergedNode->addKey(nextNode->getKeyAt(0));

					//removes previous leaves and keys from parent node which are no longer correct
					startNode->removeLeaf(nextLeafPos);
					startNode->removeLeaf(nextLeafPos - 1);

					startNode->removeKey(nextLeafPos - 1);

					//inserts the new merged node the place where the old parent key was
					startNode->insertLeafAt(mergedNode, nextLeafPos - 1);
				}

				//same has previously but with the right neighbor
				else if (rightNeighborNode != nullptr)
				{
					if (!nextNode->isLeaf())
					{
						for (size_t i = 0; i < nextNode->getLeavesCount(); i++)
							mergedNode->pushLeaf(nextNode->getLeafAt(i));
						for (size_t i = 0; i < rightNeighborNode->getLeavesCount(); i++)
							mergedNode->pushLeaf(rightNeighborNode->getLeafAt(i));
					}

					mergedNode->addKey(nextNode->getKeyAt(0));
					mergedNode->addKey(startNode->getKeyAt(nextLeafPos));
					mergedNode->addKey(rightNeighborNode->getKeyAt(0));

					startNode->removeLeaf(nextLeafPos + 1);
					startNode->removeLeaf(nextLeafPos);

					startNode->removeKey(nextLeafPos);

					startNode->insertLeafAt(mergedNode, nextLeafPos);
				}
				nextNode = mergedNode;
			}
			/*else
			{
				this->root = make_shared<Node234<T>>();

				if (leftNeighborNode != nullptr)
				{
					if (!nextNode->isLeaf())
					{
						for (size_t i = 0; i < leftNeighborNode->getLeavesCount(); i++)
							this->root->pushLeaf(leftNeighborNode->getLeafAt(i));
						for (size_t i = 0; i < nextNode->getLeavesCount(); i++)
							this->root->pushLeaf(nextNode->getLeafAt(i));
					}

					this->root->addKey(leftNeighborNode->getKeyAt(0));
					this->root->addKey(startNode->getKeyAt(nextLeafPos - 1));
					this->root->addKey(nextNode->getKeyAt(0));
				}
				else if (rightNeighborNode != nullptr)
				{
					if (!nextNode->isLeaf())
					{
						for (size_t i = 0; i <= nextNode->getLeavesCount(); i++)
							this->root->pushLeaf(nextNode->getLeafAt(i));
						for (size_t i = 0; i <= rightNeighborNode->getLeavesCount(); i++)
							this->root->pushLeaf(rightNeighborNode->getLeafAt(i));
					}

					this->root->addKey(nextNode->getKeyAt(0));
					this->root->addKey(startNode->getKeyAt(nextLeafPos));
					this->root->addKey(rightNeighborNode->getKeyAt(0));

				}
				nextNode = this->root;
			}*/
		}
	}

	_deleteKey(keyToDelete, nextNode, nodeToDelete);

}

template<typename T>
void BTree234<T>::_addKey(T key, shared_ptr<Node234<T>> startNode, shared_ptr<Node234<T>> parentNode)
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
	}
	else
	{
		//search next node to visit
		vector<T> sumKeys;
		sumKeys.push_back(key);
		sumKeys.reserve(sumKeys.size() + startNode->getKeys().size());
		sumKeys.insert(sumKeys.end(), startNode->getKeys().begin(), startNode->getKeys().end());
		sort(sumKeys.begin(), sumKeys.end());
		int nextleafPos = find(sumKeys.begin(), sumKeys.end(), key) - sumKeys.begin();
		_addKey(key, startNode->getLeafAt(nextleafPos), startNode);
	}
}


