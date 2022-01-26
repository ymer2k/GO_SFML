#pragma once
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
	Stone(TextureHolder& texture, COLOR side, float x, float y, float scale);

	// Member variables

	// Member functions
	sf::Sprite getStoneSprite();
	//Location getLocation();
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
	TextureHolder& m_texture;
	sf::Sprite m_stoneSprite;
	sf::Texture m_pieceTexture;
	sf::Vector2u m_pieceTextureSize;
	float m_x;
	float m_y;
	float m_scale;
};

