#include "Stone.h"


Stone::Stone(color side, const Location& location) : 
	 m_location(location)
	,m_side(side)
{

}

// should use an instance of Location for the location OK
// should keep which color it is OK
// Maybe even which sprite to load and use .