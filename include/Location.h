#pragma once
#include <cmath>
#include <iostream>
using std::ostream;

struct Location
{
    double latitude;
    double longitude;
    double getRow() const;
    double getCol() const;
    void setRow(double newRow);
    void setCol(double newCol);
    bool operator == (const Location& loc) const;
    bool operator != (const Location& loc) const;
    Location operator+(const Location& loc) const;
    Location& operator=(const Location& other);
    Location& operator+=(const Location& loc);

    friend ostream& operator<<(ostream& os, const Location& loc);



};