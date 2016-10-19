// Algo_Devoir2.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "FamilyTree.h"
#include "EyeColor.h"
#include "Order.h"
#include <iostream>

using namespace std;


int main()
{
	Person t("T", "t", 1960, GREEN);
	Person a("A", "a", 1961, BROWN);
	Person b("B", "b", 1962, BLUE);
	Person m("M", "n", 1963, GREEN);
	Person r("R", "r", 1964, BROWN);
	Person n("N", "n", 1965, BLUE);
	Person o("O", "o", 1966, GREEN);
	Person p("P", "p", 1967, BROWN);
	Person q("Q", "q", 1968, BLUE);
	Person s("S", "s", 1969, BLUE);

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
	cout << "Heigth of the tree: " << familyTree.getHeight() << endl;
	

	vector<Person> ancestors;
	ancestors = familyTree.getAncestorsWithColorEye(&m, GREEN, ancestors);
	cout << "Ancestors of M with color eye green" << endl;
	for (int i = 0; i < ancestors.size(); i++)
	{
		cout << ancestors[i].name << " ";
	}
	cout << endl;
	
	cout << "Descendents List of Q in pre-order:" << endl;
	vector<Person> descendants;
	descendants = familyTree.getDescendants(&q,PRE);
	for(int i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;

	cout << "Descendents List of Q in post-order:" << endl;
	descendants = familyTree.getDescendants(&q, POST);
	for (int i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;
	
	cout << "Descendents List of Q in in-order:" << endl;
	descendants = familyTree.getDescendants(&q, IN);
	for (int i = 0; i < descendants.size(); i++)
	{
		cout << descendants[i].name << " ";
	}
	cout << endl;
	system("pause");
    return 0;
}

