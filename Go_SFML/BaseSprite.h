#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class BaseSprite
{


public:
	BaseSprite(TextureHolder& texture);//, sf::Vector2i pos);
	//BaseSprite() = default;

	sf::Sprite getSprite();
	void setPosition(sf::Vector2i pos);
	sf::Vector2u getTexturePixelSize();





private:

	// member functions
	void loadSprite();

	// member variables

	TextureHolder& m_textureHolder;

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2u m_textureSize;

	sf::Vector2i m_pos;

};

