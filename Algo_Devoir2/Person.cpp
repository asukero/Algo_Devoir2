#include "stdafx.h"
#include <ctime>
#include "Person.h"

Person::~Person()
{
}

int Person::getAge() const
{
	time_t currentTime = time(0);
	struct tm now;
	localtime_s(&now, &currentTime);
	return now.tm_year + 1900 - this->yearOfBirth;
}