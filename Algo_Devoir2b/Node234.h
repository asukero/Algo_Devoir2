#pragma once
#include <vector>
#include <algorithm>
#include <memory>

template <class T>
class RBNode;

using namespace std;

template<typename T>
class Node234
{
public:
	Node234();
	Node234(vector<T> keys);
	Node234(RBNode<T> node);

	const vector<T> & getKeys();
	T getKeyAt(int i);
	const vector<shared_ptr<Node234<T>>> & getLeaves();
	shared_ptr<Node234<T>> getLeafAt(int i);
	int getKeyCount();
	int getLeavesCount();
	bool isLeaf();

	void setKeys(vector<T> keys);
	void setLeaves(vector<Node234<T>>leaves);
	bool addKey(T key);
	bool pushLeaf(shared_ptr<Node234<T>> leaf);
	void insertLeafAt(shared_ptr<Node234<T>> leaf, int pos);
	void removeLeaf(int i);
	void removeKey(int i);
	size_t getMedianPos();

	static shared_ptr<Node234<T>> convertToNode234(shared_ptr<RBNode<T>> node);

	bool operator==(Node234<T> node) const;
	template <typename V> friend ostream & operator<<(ostream & os, const Node234<V> node)
	{
		os << "Node:\nKeys: ";

		for (size_t i = 0; i < node.keys.size(); i++)
			os << node.keys[i];

		if (node.leaves.size() <= 0)
			os << "\tLeaf reached.\n";
		else
		{
			os << "Leaves:\n";
			for (size_t i = 0; i < node.leaves.size(); i++)
				os << *(node.leaves[i]);
		}
		return os;
	}

private:
	vector<T> keys;
	vector<shared_ptr<Node234<T>>> leaves;
	static const int MAX_NUMBER_KEYS = 3;
	static const int MAX_NUMBER_LEAVES = 4;

};

template<typename T>
Node234<T>::Node234()
{
	this->keys = vector<T>();
	this->leaves = vector<shared_ptr<Node234<T>>>();
}

template <typename T>
Node234<T>::Node234(RBNode<T> node)
{
	this = convertToNode234(node);
}

template<typename T>
Node234<T>::Node234(vector<T> keys)
{
	if (keys.size() >= MAX_NUMBER_KEYS)
		throw logic_error("too many keys in the vector !\n");
	if (leaves.size() >= MAX_NUMBER_LEAVES)
		throw logic_error("too many leaves in the vector !\n");
	this->keys = keys;
	this->leaves = leaves;
}

template<typename T>
const vector<T> & Node234<T>::getKeys()
{
	return this->keys;
}

template<typename T>
T Node234<T>::getKeyAt(int i)
{
	return this->keys[i];
}

template<typename T>
const vector<shared_ptr<Node234<T>>> & Node234<T>::getLeaves()
{
	return this->leaves;
}

template<typename T>
shared_ptr<Node234<T>> Node234<T>::getLeafAt(int i)
{
	return this->leaves[i];
}

template<typename T>
int Node234<T>::getKeyCount()
{
	return keys.size();
}

template<typename T>
int Node234<T>::getLeavesCount()
{
	return leaves.size();
}

template<typename T>
bool Node234<T>::isLeaf()
{
	return (this->leaves.size() <= 0);
}

template<typename T>
void Node234<T>::setKeys(vector<T> keys)
{
	this->keys = keys;
}

template<typename T>
void Node234<T>::setLeaves(vector<Node234<T>> leaves)
{
	this->leaves = leaves;
}

template<typename T>
bool Node234<T>::addKey(T key)
{
	if (this->keys.size() >= MAX_NUMBER_KEYS)
		return false;
	this->keys.push_back(key);
	sort(this->keys.begin(), this->keys.end());
	return true;
}

template<typename T>
bool Node234<T>::pushLeaf(shared_ptr<Node234<T>> leaf)
{
	if (this->leaves.size() >= MAX_NUMBER_LEAVES)
		return false;
	this->leaves.push_back(leaf);
	return true;

}

template<typename T>
void Node234<T>::insertLeafAt(shared_ptr<Node234<T>> leaf, int pos)
{
	if (this->leaves.size() >= MAX_NUMBER_LEAVES)
		throw logic_error("The leaf vector is full!\n");
	this->leaves.insert(this->leaves.begin() + pos, leaf);
}

template<typename T>
void Node234<T>::removeLeaf(int i)
{
	this->leaves.erase(this->leaves.begin() + i);
}

template<typename T>
void Node234<T>::removeKey(int i)
{
	this->keys.erase(this->keys.begin() + i);
}

template <typename T>
shared_ptr<Node234<T>> Node234<T>::convertToNode234(shared_ptr<RBNode<T>> node)
{
	if (node != nullptr)
	{
		shared_ptr<Node234> newNode(new Node234<T>());
		if (node->isLeaf())
		{
			newNode->addKey(node->getValue());
		}
		else
		{
			newNode->addKey(node->getValue());

			if (node->getLeftChild() != nullptr)
			{
				if (node->getLeftChild()->getColor() == RED)
				{
					newNode->addKey(node->getLeftChild()->getValue());
					if (node->getLeftChild()->getLeftChild() != nullptr)
						newNode->pushLeaf(convertToNode234(node->getLeftChild()->getLeftChild()));
					if (node->getLeftChild()->getRightChild() != nullptr)
						newNode->pushLeaf(convertToNode234(node->getLeftChild()->getRightChild()));
				}
				else
				{
					newNode->pushLeaf(convertToNode234(node->getLeftChild()));
				}
			}

			if (node->getRightChild() != nullptr)
			{
				if (node->getRightChild()->getColor() == RED)
				{
					newNode->addKey(node->getRightChild()->getValue());
					if (node->getRightChild()->getLeftChild() != nullptr)
						newNode->pushLeaf(convertToNode234(node->getRightChild()->getLeftChild()));
					if (node->getRightChild()->getRightChild() != nullptr)
						newNode->pushLeaf(convertToNode234(node->getRightChild()->getRightChild()));
				}
				else
				{
					newNode->pushLeaf(convertToNode234(node->getRightChild()));
				}
			}
		}
		return newNode;


	}
	throw invalid_argument("The node passed in argument is a null pointer!\n");
}

template<typename T>
size_t Node234<T>::getMedianPos()
{
	if (this->keys.size() % 2 == 0)
		throw logic_error("The number of keys has to be odd to get median key");
	return (this->keys.size()) / 2;
}

template<typename T>
bool Node234<T>::operator==(Node234<T> node) const
{
	return (this->keys == node.getKeys() && this->leaves == node.getLeaves());
}


