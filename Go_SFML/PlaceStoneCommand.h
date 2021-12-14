#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>
#include "Stone.h"

class PlaceStoneCommand : public Command
{
public:
	PlaceStoneCommand(sf::Vector2f position,Stone::COLOR side); // should take in position of the stone AND which side placed the stone.
	PlaceStoneCommand();


	void execute() override;

private:
	Stone::COLOR m_side;
	sf::Vector2f m_pos;
		
};

