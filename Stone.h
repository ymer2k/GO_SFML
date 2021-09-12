#pragma once
#include "Location.h"
class Stone
{

public:
	enum color
	{
		BLACK,
		WHITE
	};

	Stone(color side, const Location& location); // A default constructor



	
private:
	color m_side;
	Location m_location;

};

