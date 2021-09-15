#pragma once
#include <SFML/Graphics.hpp>

//This is Current Game. Keeps stuff like mouseclicks? Or something like that.


class Game
{


public:
	Game();
	void interact(sf::RenderWindow & window);

private:
	//void event();

	// Member variables
	sf::Event event;
};

