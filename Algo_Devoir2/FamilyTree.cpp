#include "stdafx.h"
#include "FamilyTree.h"
#include <vector>
#include <algorithm>
using namespace std;

FamilyTree::FamilyTree()
{
	this->root = nullptr;
	this->size = 0;
}

FamilyTree::FamilyTree(Person* root)
{
	this->root = root;
	this->size = 1;
}
FamilyTree::~FamilyTree()
{
	this->root = nullptr;
}

bool FamilyTree::isEmpty() const
{
	return this->root == nullptr;
}

int FamilyTree::getSize() const
{
	return this->size;
}

void FamilyTree::addMother(Person* person, Person* mother)
{
	if (person != nullptr && mother != nullptr)
	{
		person->mother = mother;
		this->size++;
	}
	else
	{
		throw invalid_argument("One of the argument is a NULL pointer\n");
	}
}

void FamilyTree::addFather(Person* person, Person* father)
{
	if (person != nullptr && father != nullptr)
	{
		person->father = father;
		this->size++;
	}
	else
	{
		throw invalid_argument("One of the argument is a NULL pointer\n");
	}
}

float FamilyTree::getAverageAge() const
{
	int sum = sumOfAges(this->root);
	return float(sum) / float(this->size);
}

int FamilyTree::sumOfAges(Person *person) const
{
	if (person != nullptr)
	{
		int age = person->getAge();
		return age + sumOfAges(person->father) + sumOfAges(person->mother);
	}
	return 0;
}

vector<Person> FamilyTree::getDescendants(Person *person, Order order)
{
	vector<Person> descendants;
	if (person != nullptr)
	{

		bool isFound = false;
		switch (order)
		{
		case PRE:
			descendants = _getDescendants_preOrder(person, this->root->father, descendants, &isFound);
			descendants = _getDescendants_preOrder(person, this->root->mother, descendants, &isFound);
			break;
		case POST:
			descendants = _getDescendants_postOrder(person, this->root->father, descendants, &isFound);
			descendants = _getDescendants_postOrder(person, this->root->mother, descendants, &isFound);
			break;
		case IN:
			descendants = _getDescendants_inOrder(person, this->root->father, descendants, &isFound);
			descendants = _getDescendants_inOrder(person, this->root->mother, descendants, &isFound);
			break;
		default:
			throw invalid_argument("The Order is a NULL pointer\n");
		}
		
		descendants.push_back(*this->root);
		return descendants;
	}
	throw invalid_argument("The person is a NULL pointer\n");
	
}

vector<Person> FamilyTree::_getDescendants_preOrder(Person *personToFind, Person *ancestor, vector<Person> descendants, bool *isFound) const
{

	if (personToFind == ancestor)
		*isFound = true;

	if (ancestor->father != nullptr && !*isFound)
		descendants = _getDescendants_preOrder(personToFind, ancestor->father, descendants, isFound);

	if (ancestor->mother != nullptr && !*isFound)
		descendants = _getDescendants_preOrder(personToFind, ancestor->mother, descendants, isFound);

	if (*isFound)
		descendants.push_back(*ancestor);

	return descendants;
}

vector<Person> FamilyTree::_getDescendants_postOrder(Person *personToFind, Person *ancestor, vector<Person> descendants, bool *isFound) const
{

	if (ancestor->father != nullptr && !*isFound)
		descendants = _getDescendants_postOrder(personToFind, ancestor->father, descendants, isFound);

	if (ancestor->mother != nullptr && !*isFound)
		descendants = _getDescendants_postOrder(personToFind, ancestor->mother, descendants, isFound);

	if (personToFind == ancestor)
		*isFound = true;

	if (*isFound)
		descendants.push_back(*ancestor);

	return descendants;
}

vector<Person> FamilyTree::_getDescendants_inOrder(Person *personToFind, Person *ancestor, vector<Person> descendants, bool *isFound) const
{

	if (ancestor->father != nullptr)
		descendants = _getDescendants_inOrder(personToFind, ancestor->father, descendants, isFound);

	if (personToFind == ancestor)
		*isFound = true;

	if (ancestor->mother != nullptr && !*isFound)
		descendants = _getDescendants_inOrder(personToFind, ancestor->mother, descendants, isFound);

	if (*isFound)
		descendants.push_back(*ancestor);

	return descendants;
}

vector<Person> FamilyTree::getAncestorsWithColorEye(Person *person, EyeColor eyeColor, vector<Person> ancestors) const
{
	if (person != nullptr)
	{
		if(person->eyeColor == eyeColor)
			ancestors.push_back(*person);
		if (person->father != nullptr)
			ancestors = getAncestorsWithColorEye(person->father, eyeColor, ancestors);
		if (person->mother != nullptr)
			ancestors = getAncestorsWithColorEye(person->mother, eyeColor, ancestors);
	}
	return ancestors;
}

int FamilyTree::getHeight() const
{
	if (isEmpty())
		throw logic_error("The tree is empty!\n");
	return _getHeight(this->root);
}

int FamilyTree::_getHeight(Person *node) const
{
	if (node == nullptr)
		return 0;
	return 1 + max(_getHeight(node->father), _getHeight(node->mother));
}

