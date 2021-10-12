#include "Stone.h"



//Stone::Stone(color side, const Location& location) : 
//Stone::Stone(Textures whiteAndBlackTexture, COLOR side, int x, int y) :
Stone::Stone(COLOR side, int x, int y) :
	m_location(x, y) // Instead of m_location(location) // Not used now
//	,m_stoneTextures(whiteAndBlackTexture)
	,m_x(x)
	,m_y(y)
	,m_side(side)
	,m_pieceTexture()
	,m_pieceTextureSize()
	,m_black(sf::Vector2f(19, 19)) //TODO Change this to m_pieceTextureSize.x and .y later //probably first set to 0,0 and then use some "set texture size method".
	,m_white(sf::Vector2f(19, 19))
	,m_stone(sf::Vector2f(19, 19))
{
	 


	loadSprite();
	setPosition();
}



sf::RectangleShape Stone::getStone()
{
	return m_stone;
}

Location Stone::getLocation()
{
	return m_location;
}

Stone::COLOR Stone::getSide()
{
	return m_side;
}



void Stone::loadSprite()
{
	//m_pieceTexture.loadFromFile("Sprites/white_black.png");
	//m_stone.setTexture(&m_pieceTexture); //here we set the texture eventhough its the whole texture
	m_stone.setTexture(m_stoneTextures.getTexture());

	m_pieceTextureSize = m_pieceTexture.getSize();
	//here we split the texture into pieces.
	m_pieceTextureSize.x /= 2;
	m_pieceTextureSize.y /= 1; //because only one row :)


	//Get a sub texture from the collected texture Black_white.png
	m_white.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	m_black.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y)); //First two parameters are the starting positions in the texture and the other two parameters are the size of the texture

	// Set stone depending on which side plays.
	if (m_side == BLACK)
	{
		m_stone.setTextureRect(sf::IntRect(m_pieceTextureSize.x, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));
	}else
		m_stone.setTextureRect(sf::IntRect(0, 0, m_pieceTextureSize.x, m_pieceTextureSize.y));

}

void Stone::setPosition()
{
	m_stone.setPosition(m_x, m_y);
}

// should use an instance of Location for the location OK
// should keep which color it is OK
// Maybe even which sprite to load and use .