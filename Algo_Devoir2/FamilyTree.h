#pragma once
#include <vector>
#include "Person.h"
#include "Order.h"

using namespace std;

class FamilyTree
{
public:

	FamilyTree();
	FamilyTree(Person*);
	virtual ~FamilyTree();

	bool isEmpty() const;
	int getSize() const;
	void addMother(Person*, Person*);
	void addFather(Person*, Person*);
	float getAverageAge() const;

	vector<Person> getDescendants(Person* person, Order order);
	vector<Person> getAncestorsWithColorEye(Person * person, EyeColor eyeColor, vector<Person> ancestors) const;

	int getHeight() const;


private:
	Person *root;
	int size;
	int sumOfAges(Person*) const;
	vector<Person> _getDescendants_preOrder(Person* personToFind, Person* ancestor, vector<Person> descendants, bool* isFound) const; 
	vector<Person> _getDescendants_postOrder(Person* personToFind, Person* ancestor, vector<Person> descendants, bool* isFound) const;
	vector<Person> _getDescendants_inOrder(Person * personToFind, Person * ancestor, vector<Person> descendants, bool* isFound) const;
	int _getHeight(Person * node) const;

};

