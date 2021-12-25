#include "Stone.h"




Stone::Stone(TextureHolder &texture, COLOR side, int x, int y) : //Change int x, int y to sf::vector2i
	m_location(x, y) // Instead of m_location(location) // Not used now
	//,m_stoneTextures(whiteAndBlackTexture)
	,m_texture(texture)
	,m_x(x)
	,m_y(y)
	,m_side(side)
	,m_pieceTexture()
	,m_pieceTextureSize()
{

	loadSprite();
	setPosition(m_x,m_y);
}



sf::Sprite Stone::getStoneSprite()
{
	return m_stoneSprite;
}

Location Stone::getLocation()
{
	return m_location;
}



Stone::COLOR Stone::getSide()
{
	return m_side;
}

void Stone::setSide(Stone::COLOR side)
{
	m_side = side;
}

void Stone::setSprite(Stone::COLOR side)
{
	if (side == BLACK)
	{
		m_stoneSprite.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	}
	else
		m_stoneSprite.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
}



void Stone::loadSprite()
{
	//For sprite 
	m_stoneSprite.setTexture(m_texture.get(TextureHolder::ID::Stone));

	m_pieceTextureSize = m_texture.get(TextureHolder::ID::Stone).getSize();
	//here we split the texture into pieces.
	m_pieceTextureSize.x /= 2;
	m_pieceTextureSize.y /= 1; //because only one row :)


	//SPRITE
		// Set stone depending on which side plays.
	if (m_side == BLACK)
	{
		m_stoneSprite.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	}
	else
		m_stoneSprite.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
}

void Stone::setPosition(int x, int y)
{
	// Save the current postion in member variables.
	m_x = x;
	m_y = y;
	//Update the position of the texture.
	m_stoneSprite.setPosition(x, y);
}

sf::Vector2u Stone::getStonePixelSize()
{
	return m_pieceTextureSize;
}

// should use an instance of Location for the location OK
// should keep which color it is OK
// Maybe even which sprite to load and use .