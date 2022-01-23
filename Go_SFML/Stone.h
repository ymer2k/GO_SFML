#pragma once
#include "Location.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Stone
{

public:
	enum class COLOR
	{
		NO_STONE,
		BLACK,
		BLACK_AREA,
		WHITE,
		WHITE_AREA
	};

	// Member variables

	//Stone(color side, const Location& location); // A default constructor BECAUSE of the default consturctor the Stone vector will not be empty, it will be filled of these default Stones...
	//How to avoid printing these default stones? Have a default NO_STONE value? and check if NO_STONE dont draw?
	//Stone(Textures *whiteAndBlackTexture, COLOR side = NO_STONE, int x = 0, int y = 0); // maybe stone should have an ID as well, stone 1 stone 2 etc. Passing Textures objet by reference instead of by value
	Stone(TextureHolder& texture, COLOR side, float x, float y, float scale);
	//Stone(COLOR side = NO_STONE, int x = 0, int y = 0); // maybe stone should have an ID as well, stone 1 stone 2 etc.
	



	// Member functions
	sf::Sprite getStoneSprite();
	Location getLocation();
	COLOR getSide();
	void setSide(Stone::COLOR side);
	void setSprite(Stone::COLOR side);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setScale(float x, float y);
	void setOrigin(float x, float y);
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

	float m_x;
	float m_y;

	float m_scale;



};

