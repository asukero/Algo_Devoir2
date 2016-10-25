// Algo_Devoir2.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "FamilyTree.h"
#include <iostream>

using namespace std;


int main()
{
	Person t("Thomas", "Dupont", 1915, GREEN);
	Person a("Anatole", "Dupont", 1941, BROWN);
	Person b("Brigitte", "Tremblay", 1939, BLUE);
	Person m("Marc", "Dupont", 1963, GREEN);
	Person r("Regis", "Dupont", 1994, BROWN);
	Person n("Noemie", "Bouchard", 1965, BLUE);
	Person o("Olivier", "Bouchard", 1936, GREEN);
	Person p("Patricia", "Martin", 1942, BROWN);
	Person q("Quentin", "Martin", 1912, BLUE);
	Person s("Sophie", "Daniel", 1918, BLUE);

			//   		R
			//	   M	     N
			//  A	  B	  O	     P
			//T				   Q    S


	FamilyTree familyTree(&r);
	familyTree.addFather(&r, &m);
	familyTree.addMother(&r, &n);
	familyTree.addFather(&m, &a);
	familyTree.addMother(&m, &b);
	familyTree.addFather(&a, &t);
	familyTree.addFather(&n, &o);
	familyTree.addMother(&n, &p);
	familyTree.addFather(&p, &q);
	familyTree.addMother(&p, &s);

	cout << "Number of person in the tree: " << familyTree.getSize() << endl;
	cout << "Average age: " << familyTree.getAverageAge() << endl;
	cout << "Height of the tree: " << familyTree.getHeight() << endl;
	

	vector<Person> ancestors;
	ancestors = familyTree.getAncestorsWithColorEye(&m, GREEN, ancestors);
	cout << "Ancestors of Marc with color eye green" << endl;
	for (size_t i = 0; i < ancestors.size(); i++)
	{
		cout << ancestors[i].name << " ";
	}
	cout << endl;
	
	cout << "Descendents List of Quentin in pre-order:" << endl;
	vector<Person> descendants;
	descendants = familyTree.getDescendants(&q,PRE);
	for(size_t i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;

	cout << "Descendents List of Quentin in post-order:" << endl;
	descendants = familyTree.getDescendants(&q, POST);
	for (size_t i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;
	
	cout << "Descendents List of Quentin in in-order:" << endl;
	descendants = familyTree.getDescendants(&q, IN);
	for (size_t i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;
	system("pause");
    return 0;
}

