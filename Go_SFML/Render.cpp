#include "Render.h"
#include "Board.h"

Render::Render() : //Constructor
	WINDOW_WIDTH(1024) 
	,WINDOW_HEIGHT(720)
	,BOARDER_SIZE(5)
{
	initializeWorld();
}

void Render::initializeWorld()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Go"); // The create  function is used when we create the window AFTER initilization.
	window.setVerticalSyncEnabled(true);
	view = window.getView();
	view.setCenter(sf::Vector2f(WINDOW_WIDTH/4, WINDOW_HEIGHT/4)); // divide by 4 just to get a good size
	view.setSize(sf::Vector2f(WINDOW_WIDTH/2 + BOARDER_SIZE, WINDOW_HEIGHT/2 + BOARDER_SIZE)); // divide by 2 just to get a good size
	window.setView(view); // apply the changes made to the view to the current window!
}




