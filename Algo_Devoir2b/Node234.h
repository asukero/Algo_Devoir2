#pragma once
#include <vector>

using namespace std;

template<typename T>
class Node234
{
public:
	Node234();
	Node234(vector<T> keys, vector<Node234<T>*> leaves);
	virtual ~Node234();

	vector<T> getKeys();
	vector<Node234<T>> getLeaves();
	int getKeyCount();
	int getLeavesCount();

	void setKeys(vector<T> keys);
	void setLeaves(vector<Node234<T>*>leaves);
	void addKey(T key);
	void addLeaf(Node234<T> *leaf);

private:
	vector<T> keys;
	vector<Node234<T>*> leaves;

};

template<typename T>
Node234<T>::Node234(vector<T> keys = vector<T>(), vector<Node234<T>*> leaves = vector<Node234<T>*>())
{
	this->keys = keys;
	this->leaves = leaves;
}

template<typename T>
inline vector<T> Node234<T>::getKeys()
{
	return this->keys;
}

template<typename T>
inline vector<Node234<T>> Node234<T>::getLeaves()
{
	return this->leaves;
}

template<typename T>
inline int Node234<T>::getKeyCount()
{
	return keys.size();
}

template<typename T>
inline int Node234<T>::getLeavesCount()
{
	return leaves.size();
}

template<typename T>
inline void Node234<T>::setKeys(vector<T> keys)
{
	this->keys == keys;
}

template<typename T>
inline void Node234<T>::setLeaves(vector<Node234<T>*> leaves)
{
	this->leaves = leaves;
}

template<typename T>
inline void Node234<T>::addKey(T key)
{
	if (this->keys.size() >= 3)
		throw logic_error("keys vector is full\n");
	this->keys.push_back(key);
}

template<typename T>
inline void Node234<T>::addLeaf(Node234<T> *leaf)
{
	if (this->leaves.size() >= 4)
		throw logic_error("leaves vector is full\n");
	this->leaves.push_back(leaf);

}



