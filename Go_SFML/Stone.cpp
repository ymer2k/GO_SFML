#include "Stone.h"

//Stone::Stone(TextureHolder &texture, COLOR side, float x, float y, float scale) : //TODO Change int x, int y to sf::vector2i
//	m_texture(texture)
//	,m_x(x)
//	,m_y(y)
//	,m_side(side)
//	,m_pieceTexture()
//	,m_pieceTextureSize()
//	,m_scale(scale)
//{
//	loadSprite();
//	setPosition(m_x,m_y);
//}

Stone::Stone(COLOR side, float x, float y, float scale):
	 m_x(x)
	, m_y(y)
	, m_side(side)
	, m_pieceTexture()
	, m_pieceTextureSize()
	, m_scale(scale)
{

	setPosition(m_x, m_y);
}


sf::Sprite Stone::getStoneSprite()
{
	return m_stoneSprite;
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
	if (side == Stone::COLOR::BLACK)
	{
		m_stoneSprite.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	}
	else
		m_stoneSprite.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
}

void Stone::loadSprite(TextureHolder& texture)
{
	//For sprite 
	m_stoneSprite.setTexture(texture.get(TextureHolder::ID::Stone));

	m_pieceTextureSize = texture.get(TextureHolder::ID::Stone).getSize();
	//here we split the texture into pieces.
	m_pieceTextureSize.x /= 2;
	m_pieceTextureSize.y /= 1; //because only one row :)

	//SPRITE
	// Set stone depending on which side plays.
	if (m_side == Stone::COLOR::BLACK) // || BLACK_TERRITORY
	{
		m_stoneSprite.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	}
	else
		m_stoneSprite.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));

	// Set scale of sprite
	m_stoneSprite.setScale(m_scale, m_scale);
}


void Stone::setPosition(float x, float y)
{
	// Save the current postion in member variables.
	m_x = x;
	m_y = y;
	//Update the position of the texture.
	m_stoneSprite.setPosition(x, y);
}

sf::Vector2f Stone::getPosition()
{
	sf::Vector2f retVal = m_stoneSprite.getPosition();
	return retVal;
}

void Stone::setScale(float x, float y)
{
	m_stoneSprite.setScale(x, y);
}

void Stone::setOrigin(float x, float y)
{
	m_stoneSprite.setOrigin(x, y);
}

sf::Vector2u Stone::getStonePixelSize()
{
	return m_pieceTextureSize;
}
