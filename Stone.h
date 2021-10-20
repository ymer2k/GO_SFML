#pragma once
#include "Location.h"
#include "Textures.h"
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
	sf::RectangleShape getStone();
	sf::Sprite getStoneSprite();
	Location getLocation();
	COLOR getSide();
	void setSide(Stone::COLOR side);
	void setSprite(Stone::COLOR side);


private:
	// member functions
	void loadSprite();
	void setPosition();

	// member variables
	COLOR m_side;
	Location m_location;
	Textures * m_stoneTextures; // an object that has a getter function that returns a pointer to the two stone textures. Gets this object as an argument in the constructor.
	// And It is in Game.cpp where we create Stone objects so its actually Game that passes the Texture object to the Stone class.
	//We could skip sending in the Texture as an argument in the constructor and just use it directly here... Why Do I need it as an input arguemnt?
	TextureHolder& m_texture;

	sf::Sprite m_stoneSprite;
	sf::Texture m_pieceTexture;
	sf::Vector2u m_pieceTextureSize;
	sf::RectangleShape m_black;
	sf::RectangleShape m_white;
	sf::RectangleShape m_stone;
	int m_x;
	int m_y;



};

