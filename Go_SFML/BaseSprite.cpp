#include "BaseSprite.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

BaseSprite::BaseSprite(TextureHolder& texture)://, sf::Vector2i pos):
	m_textureHolder(texture)
//, m_pos(pos)
{
	//m_sprite.setTexture(m_textureHolder.get(TextureHolder::ID::Stone));
	//m_sprite.setPosition(m_pos.x, m_pos.y);

}

sf::Sprite BaseSprite::getSprite()
{
	return m_sprite;
}

void BaseSprite::setPosition(sf::Vector2i pos)
{
	m_pos = pos;
	m_sprite.setPosition(pos.x, pos.y);
}

void BaseSprite::loadSprite(TextureHolder::ID id)
{
	//For sprite 
	m_sprite.setTexture(m_textureHolder.get(id));

}

void BaseSprite::loadTransparentSprite()
{
	m_sprite.setTexture(m_texture);
}

void BaseSprite::setScale(float x, float y)
{
	m_sprite.scale(x, y);
}

void BaseSprite::setOrigin(float x, float y)
{
	//std::cout << m_sprite.getOrigin().x << std::endl;
	m_sprite.setOrigin(x, y);
}
