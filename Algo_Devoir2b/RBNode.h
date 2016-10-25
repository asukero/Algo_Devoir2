#pragma once

#include <memory>

using namespace std;

enum RBTreeColor { RED, BLACK };
template <typename T>
class RBNode
{
public:
	RBNode();
	RBNode(T value);
	RBNode(shared_ptr<Node234<T>> node);

	T getValue();
	RBTreeColor getColor() const;
	shared_ptr<RBNode<T>> getLeftChild();
	shared_ptr<RBNode<T>> getRightChild();
	shared_ptr<RBNode<T>> getParent();

	void setValue(T value);
	void setColor(RBTreeColor color);
	void setLeftChild(shared_ptr<RBNode<T>> node);
	void setRightChild(shared_ptr<RBNode<T>> node);
	void setParent(shared_ptr<RBNode<T>> node);
	bool isLeaf();

	static shared_ptr<RBNode<T>> convertToRBNode(shared_ptr<Node234<T>> node);

	template <typename V> friend ostream & operator<<(ostream & os, const RBNode<V> node)
	{
		string color;
		if (node.color == RED)
			color = "Red";
		else
			color = "Black";

		os << "Node:\nValue: " << node.value << "Color: " << color << endl;

		if (node.left != nullptr)
			os << "Left child:\n" << *(node.left);
		if (node.right != nullptr)
			os << "Right child:\n" << *(node.right);

		return os;
	}

private:
	T value;
	RBTreeColor color;
	shared_ptr<RBNode<T>> left;
	shared_ptr<RBNode<T>> right;
	shared_ptr<RBNode<T>> parent;
};

template <typename T>
RBNode<T>::RBNode() : color(BLACK)
{
}

template<typename T>
RBNode<T>::RBNode(T value)
{
	this->value = value;
	this->color = BLACK;

}

template<typename T>
RBNode<T>::RBNode(shared_ptr<Node234<T>> node)
{
	this = convertToRBNode(node);
}

template<typename T>
T RBNode<T>::getValue()
{
	return this->value;
}

template<typename T>
RBTreeColor RBNode<T>::getColor() const
{
	return this->color;
}

template<typename T>
shared_ptr<RBNode<T>> RBNode<T>::getLeftChild()
{
	return this->left;
}

template <typename T>
shared_ptr<RBNode<T>> RBNode<T>::getRightChild()
{
	return this->right;
}

template<typename T>
shared_ptr<RBNode<T>> RBNode<T>::getParent()
{
	return this->parent;
}

template<typename T>
void RBNode<T>::setValue(T value)
{
	this->value = value;
}

template<typename T>
void RBNode<T>::setColor(RBTreeColor color)
{
	this->color = color;
}

template<typename T>
void RBNode<T>::setLeftChild(shared_ptr<RBNode<T>> node)
{
	this->left = node;
}

template<typename T>
void RBNode<T>::setRightChild(shared_ptr<RBNode<T>> node)
{
	this->right = node;
}

template <typename T>
bool RBNode<T>::isLeaf()
{
	return (this->left == nullptr && this->right == nullptr);
}

template<typename T>
void RBNode<T>::setParent(shared_ptr<RBNode<T>> node)
{
	this->parent = node;
}

template<typename T>
shared_ptr<RBNode<T>> RBNode<T>::convertToRBNode(shared_ptr<Node234<T>> node)
{

	if (node != nullptr) {

		shared_ptr<RBNode<T>> newNode(new RBNode<T>());
		shared_ptr<RBNode<T>> childNode(new RBNode<T>());
		shared_ptr<RBNode<T>> leftChildNode(new RBNode<T>());
		shared_ptr<RBNode<T>> rightChildNode(new RBNode<T>());

		switch (node->getKeyCount())
		{
		case 1:
			newNode->setValue(node->getKeyAt(0));
			if (!node->isLeaf())
			{
				newNode->setLeftChild(convertToRBNode(node->getLeafAt(0)));
				newNode->setRightChild(convertToRBNode(node->getLeafAt(1)));
			}
			break;
		case 2:
			newNode->setValue(node->getKeyAt(1));

			childNode->setValue(node->getKeyAt(0));
			childNode->setColor(RED);
			newNode->setLeftChild(childNode);
			if (!node->isLeaf())
			{
				childNode->setLeftChild(convertToRBNode(node->getLeafAt(0)));
				childNode->setRightChild(convertToRBNode(node->getLeafAt(1)));
				newNode->setRightChild(convertToRBNode(node->getLeafAt(2)));
			}
			break;
		case 3:
			newNode->setValue(node->getKeyAt(1));

			leftChildNode->setValue(node->getKeyAt(0));
			leftChildNode->setColor(RED);
			rightChildNode->setValue(node->getKeyAt(2));
			rightChildNode->setColor(RED);
			newNode->setLeftChild(leftChildNode);
			newNode->setRightChild(rightChildNode);

			if (!node->isLeaf())
			{
				leftChildNode->setLeftChild(convertToRBNode(node->getLeafAt(0)));
				leftChildNode->setRightChild(convertToRBNode(node->getLeafAt(1)));
				rightChildNode->setLeftChild(convertToRBNode(node->getLeafAt(2)));
				rightChildNode->setRightChild(convertToRBNode(node->getLeafAt(3)));
			}
			break;
		default:
			throw logic_error("The node passed in argument is not a 234 Node!\n");

		}
		return newNode;
	}
	throw invalid_argument("The node passed in argument is a null pointer!\n");

}



