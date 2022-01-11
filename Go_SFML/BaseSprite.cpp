#include "BaseSprite.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

BaseSprite::BaseSprite(TextureHolder& texture)://, sf::Vector2i pos):
	m_textureHolder(texture)
//, m_pos(pos)
{
	m_sprite.setTexture(m_textureHolder.get(TextureHolder::ID::Stone));
	m_sprite.setPosition(m_pos.x, m_pos.y);

}

void BaseSprite::loadSprite()
{
	//For sprite 
	m_sprite.setTexture(m_textureHolder.get(TextureHolder::ID::Stone));

}
