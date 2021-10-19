#include "TextureHolder.h"

TextureHolder::TextureHolder()
{


}

void TextureHolder::load(ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture()); // Create a unique pointer of type sf::Texture and allocate space for a sf::Texture
	texture->loadFromFile(filename); // load the texture from the given filename

	// insert into map, move actually moves the texture into the map and texture should become "empty".
	// we do this instead of copying.
	m_textureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(ID id)
{
	auto found = m_textureMap.find(id);
	return *found->second;
}

const sf::Texture& TextureHolder::get(ID id) const
{
	auto found = m_textureMap.find(id);
	return *found->second;
}
