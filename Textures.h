#pragma once
#include <SFML/Graphics.hpp>


class Textures
{



public:
	Textures(); //Default Constructor. For now default constructor, later have input decied which texture. Now we only have one (black and white combined)

	sf::Texture* getTexture();


private:
	sf::Texture m_pieceTexture;
	sf::Texture *m_pieceTexture_p = new sf::Texture;

};

