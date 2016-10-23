#pragma once
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

template<typename T>
class Node234
{
public:
	Node234();
	Node234(vector<T> keys);
	//virtual ~Node234();

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
	void removeLeaf(int pos);

	size_t getMedianPos();

	bool operator==(Node234<T> node) const;

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
void Node234<T>::removeLeaf(int pos)
{
	this->leaves.erase(this->leaves.begin() + pos);
}

template<typename T>
size_t Node234<T>::getMedianPos()
{
	if (this->keys.size() % 2 == 0)
		throw logic_error("The number of keys has to be odd to get median key");
	return (this->keys.size() ) / 2;
}

template<typename T>
bool Node234<T>::operator==(Node234<T> node) const
{
	return (this->keys == node.getKeys() && this->leaves == node.getLeaves());
}



