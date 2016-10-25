#pragma once
#include <string>
using namespace std;

enum EyeColor
{ BLUE, GREEN, BROWN };

class Person
{
public:
	Person *father;
	Person *mother;
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
