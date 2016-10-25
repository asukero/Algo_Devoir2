#include "stdafx.h"
#include "LegoPiece.h"

LegoPiece::LegoPiece()
{
	this->id = "";
	this->description = "";
	this->category = "";
}

LegoPiece::LegoPiece(string id, string description, string category)
{
	this->id = id;
	this->description = description;
	this->category = category;
}

LegoPiece::LegoPiece(const LegoPiece & copy)
{
	this->id = copy.id;
	this->description = copy.description;
	this->category = copy.category;
}

LegoPiece::~LegoPiece()
{
}

string LegoPiece::getId() const
{
	return this->id;
}

void LegoPiece::setId(string id)
{
	this->id = id;
}

string LegoPiece::getDescription() const
{
	return this->description;
}

void LegoPiece::setDescription(string description)
{
	this->description = description;
}

string LegoPiece::getCategory() const
{
	return this->category;
}

void LegoPiece::setCategory(string category)
{
	this->category = category;
}

bool LegoPiece::operator>(const LegoPiece legoPiece) const
{
	return this->id > legoPiece.getId();
}

bool LegoPiece::operator<(const LegoPiece legoPiece) const
{
	return this->id < legoPiece.getId();
}

bool LegoPiece::operator==(const LegoPiece legoPiece) const
{
	return this->id == legoPiece.getId();
}

ostream & operator<<(ostream & os, const LegoPiece & piece)
{
	os << "\tid: " << piece.id << " description: " << piece.description << " category: " << piece.description << "\n";
	return os;
}
