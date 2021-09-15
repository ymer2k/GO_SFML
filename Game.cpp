#include "Game.h"

Game::Game()
{
}

void Game::interact(sf::RenderWindow & window)
{
    while (window.pollEvent(event))
    {
        // Maybe use switch case instead. Add mouse click etc!
        if (event.type == sf::Event::Closed)
            window.close();

        
        if (event.type == sf::Event::MouseButtonReleased)
        {
            //released = true;
        }
    }
}



void event()
{
	//run event loop
}
