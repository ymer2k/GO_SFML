#pragma once
#include "Location.h"
#include <SFML/Graphics.hpp>

class Stone
{

public:
	enum COLOR
	{
		NO_STONE,
		BLACK,
		WHITE
	};

	// Member variables

	//Stone(color side, const Location& location); // A default constructor BECAUSE of the default consturctor the Stone vector will not be empty, it will be filled of these default Stones...
	//How to avoid printing these default stones? Have a default NO_STONE value? and check if NO_STONE dont draw?
	Stone(COLOR side = NO_STONE, int x = 0, int y = 0); // maybe stone should have an ID as well, stone 1 stone 2 etc.


	// Member functions
	sf::RectangleShape getStone();
	Location getLocation();
	COLOR getSide();






	
private:
	// member functions
	void loadSprite();
	void setPosition();

	// member variables
	COLOR m_side;
	Location m_location;

	sf::Texture m_pieceTexture;
	sf::Vector2u m_pieceTextureSize;
	sf::RectangleShape m_black;
	sf::RectangleShape m_white;
	sf::RectangleShape m_stone;
	int m_x;
	int m_y;



};

