#pragma once
#include "Location.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

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
	//Stone(Textures *whiteAndBlackTexture, COLOR side = NO_STONE, int x = 0, int y = 0); // maybe stone should have an ID as well, stone 1 stone 2 etc. Passing Textures objet by reference instead of by value
	Stone(TextureHolder& texture, COLOR side, int x, int y);
	//Stone(COLOR side = NO_STONE, int x = 0, int y = 0); // maybe stone should have an ID as well, stone 1 stone 2 etc.
	



	// Member functions
	sf::Sprite getStoneSprite();
	Location getLocation();
	COLOR getSide();
	void setSide(Stone::COLOR side);
	void setSprite(Stone::COLOR side);
	void setPosition(int x, int y);
	sf::Vector2u getStonePixelSize();



private:
	// member functions
	void loadSprite();


	// member variables
	COLOR m_side;
	Location m_location;

	TextureHolder& m_texture;

	sf::Sprite m_stoneSprite;
	sf::Texture m_pieceTexture;
	sf::Vector2u m_pieceTextureSize;

	int m_x;
	int m_y;



};

