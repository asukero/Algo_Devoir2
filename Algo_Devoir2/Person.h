#pragma once
#include <string>
#include "EyeColor.h"

using namespace std;
class Person
{
public:
	Person *father;
	Person *mother;
	//int height;
	string name;
	string lastName;
	int yearOfBirth;
	EyeColor eyeColor;

	Person(string name, string lastName, int yearOfBirth, EyeColor eyeColor, Person* father = nullptr, Person* mother = nullptr )
	{
		this->father = father;
		this->mother = mother;
		this->name = name;
		this->lastName = lastName;
		this->yearOfBirth = yearOfBirth;
		this->eyeColor = eyeColor;

	}
	virtual ~Person();

	int getAge() const;
};
