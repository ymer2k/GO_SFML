#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
// class structure taken from SFML Game Development book


class TextureHolder
{

public:
	TextureHolder();

	enum class ID
	{
		Stone,
		Board,
	};

	// given the ID and filename we "load" the map with the requested texture.
	void load(ID id, const std::string& filename);
	// A get function to get the approprite texture depending on the ID we pass in.
	sf::Texture& get(ID id);

	const sf::Texture& get(ID id) const;

private:
	// a map that contains pointers to sf::Textures (key is the ID)
	std::map<ID, std::unique_ptr<sf::Texture>> m_textureMap;
};

