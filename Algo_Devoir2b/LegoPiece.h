#pragma once
#include <string>

using namespace std;

class LegoPiece
{
public:

	LegoPiece();
	LegoPiece(string, string, string);
	LegoPiece(const LegoPiece &copy);
	virtual ~LegoPiece();

	string getId() const;
	void setId(string id);
	string getDescription() const;
	void setDescription(string description);
	string getCategory() const;
	void setCategory(string category);
	
	bool operator>(const LegoPiece legoPiece) const;
	bool operator<(const LegoPiece legoPiece) const;
	bool operator==(const LegoPiece legoPiece) const;
	friend ostream& operator<<(ostream& os, const LegoPiece& piece);

private:
	string id;
	string description;
	string category;

};
