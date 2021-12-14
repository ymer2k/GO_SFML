#include "PlaceStoneCommand.h"

PlaceStoneCommand::PlaceStoneCommand(sf::Vector2f position, Stone::COLOR side):
	m_side(Stone::COLOR::NO_STONE)
	, m_pos(sf::Vector2f(0.0f,0.0f))
{
}

PlaceStoneCommand::PlaceStoneCommand()
{
}

void PlaceStoneCommand::execute() // Ta in ett stone object här? //Later have Stone inherit from an "entity" class and have entity as input argument!
{
	//Sätt stone objects position and color here
}
