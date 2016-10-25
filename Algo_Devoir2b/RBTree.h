#pragma once
#include "BTree234.h"
#include "RBNode.h"
using namespace std;


template<typename T>
class RBTree
{
public:
	RBTree();
	RBTree(shared_ptr<RBNode<T>> rootNode);
	RBTree(BTree234<T> tree);
	static RBTree<T> convertToRBTree(BTree234<T> tree);
	shared_ptr<RBNode<T>> getRoot();

	template <typename V> friend ostream & operator<<(ostream & os, const RBTree<V> tree)
	{
		os << "RBTree: (print in pre-order)\n" << *(tree.root);
		return os;
	}
private:
	shared_ptr<RBNode<T>> root;
};

template<typename T>
RBTree<T>::RBTree()
{
	this->root = make_shared<RBNode<T>>();
}

template<typename T>
RBTree<T>::RBTree(shared_ptr<RBNode<T>> rootNode)
{
	this->root = rootNode;
}

template<typename T>
RBTree<T>::RBTree(BTree234<T> tree)
{
	convertToRBTree(tree);
}

template<typename T>
RBTree<T> RBTree<T>::convertToRBTree(BTree234<T> tree)
{
	shared_ptr<RBNode<T>> rootNode = RBNode<T>::convertToRBNode(tree.getRoot());
	return RBTree(rootNode);

}

template <typename T>
shared_ptr<RBNode<T>> RBTree<T>::getRoot()
{
	return this->root;
}
