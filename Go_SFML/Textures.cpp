#include "Textures.h"


Textures::Textures()
{
	m_pieceTexture.loadFromFile("Sprites/white_black.png");
}

sf::Texture* Textures::getTexture()
{
	return &m_pieceTexture;
}
