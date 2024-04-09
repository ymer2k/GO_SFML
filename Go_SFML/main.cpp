#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Game.h"

/*
Made by Jonas T
Version 1.0
2022-01-26
*/

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
int main()
{    
    // Used to keep track of the current state of the game, i.e score, whos turn it is , when someone won, legal move etc.
    // If GameState is ONLY used as an input argument in "currentGame" methods, then change it to just be a member variable
    // in the Game class!
    GameLogic GameState;

    Render world;
    Game currentGame;
    
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    static bool first = true;

    while (world.window.isOpen()) // the main game loop
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt; // add the time it took to update the game + render the game;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            //We stay in this loop and update the game without rendering until the condition returns false.
            timeSinceLastUpdate -= TimePerFrame;

            /*
            * //This only ran the update function on a click  I removed it. I might have done it because I had that the click registers on press down and not on the release so immediatly
            * //after choosing a board size we got a click on the board and this was a simple fix?
            if (currentGame.interact(world.window) || first) // Update the screen only on event, makes the timeframes useless.
            {
            currentGame.update(world.window, GameState); //Handles all the game logic from here
            first = false; // Update on click so first screen will not be shown unless we automatically show first.
            }
            */


            //currentGame.interact(world.window);
            //currentGame.update(world.window, GameState); //Handles all the game logic from here

        }
        currentGame.interact(world.window);
        currentGame.update(world.window, GameState); //Handles all the game logic from here

        world.window.clear();
        currentGame.drawGame(world.window);  // does all the rednering on screen
        world.window.display();
    }
    return 0;
}