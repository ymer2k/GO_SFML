#pragma once
// keeps track of the location of an object.


class Location
{


public:
	Location(); // A default constructor
	Location(int x, int y); // A specific contructor

	// Acces functions
	void setLocation(int x, int y);
	int getx();
	int gety();

private:
	int m_x;
	int m_y;
};

