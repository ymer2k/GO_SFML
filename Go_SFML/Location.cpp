#include "Location.h"

Location::Location() : 
	 m_x(0)
	,m_y(0)
{}

Location::Location(int x, int y) :
	 m_x(x)
	,m_y(y)
{

}

void Location::setLocation(int x, int y)
{
	m_x = x;
	m_y = y;
}

int Location::getx()
{
	return m_x;
}

int Location::gety()
{
	return m_y;
}
