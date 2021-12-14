#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	InputHandler(sf::RenderWindow& window);
	void handleInput();


	//Methods to bind commands


private:
	Command* m_leftMouseClick;
	sf::RenderWindow& m_window;
};

