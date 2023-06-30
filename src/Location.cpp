#include "Location.h"

double Location::getRow() const { return latitude; }

double Location::getCol() const { return longitude; }

void Location::setRow(double newRow) { latitude = newRow; }

void Location::setCol(double newCol) { longitude = newCol; }

bool Location::operator == (const Location& loc) const { return (latitude == loc.latitude && longitude == loc.longitude); }

bool Location::operator != (const Location& loc) const { return (latitude != loc.latitude || longitude != loc.longitude); }

Location& Location::operator=(const Location& other) {
	if (this != &other) {
		latitude = other.latitude;
		longitude = other.longitude;
	}
	return *this;
}

Location Location::operator+(const Location& loc) const
{
	Location newLoc;
	newLoc.setRow(latitude + loc.latitude);
	newLoc.setCol(longitude + loc.longitude);
	return newLoc;
}

Location& Location::operator+=(const Location& loc)
{
	(*this) = (*this) + loc;
	return *this;
}

ostream& operator<<(ostream& os, const Location& loc)
{
	os << '(' << loc.latitude << ", " << loc.longitude << ')';
	return os;
}


