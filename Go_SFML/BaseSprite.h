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
	void loadSprite(TextureHolder::ID id);
	void loadTransparentSprite();
	void setScale(float x, float y);
	void setOrigin(float x, float y);
	





private:

	// member functions

	// member variables

	TextureHolder& m_textureHolder;

	sf::Image m_image;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2u m_textureSize;

	sf::Vector2i m_pos;

};

