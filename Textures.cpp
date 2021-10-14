#include "Textures.h"


Textures::Textures()
{
	m_pieceTexture.loadFromFile("Sprites/white_black.png");
	m_pieceTexture_p = &m_pieceTexture;

}

sf::Texture* Textures::getTexture()
{
	return m_pieceTexture_p;
}
