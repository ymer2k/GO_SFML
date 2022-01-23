#include "Render.h"
#include "Board.h"


Render::Render() : //Constructor
	WINDOW_WIDTH(1024) // most recent 344//Board Size *2 + BOARDER_SIZE=347 // round to 348 to get even number to render at integer positions
	,WINDOW_HEIGHT(720) // most recent 600
	,BOARDER_SIZE(5)
{
	initializeWorld();
}

void Render::initializeWorld()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Go"); // the create  function is used when we create the window AFTER initilization.
	window.setVerticalSyncEnabled(true);
	view = window.getView();
	// almost everything here should be member variables I guess Textures, sprites, shapes, fonts, etc.
	float aspectRatio =(float) WINDOW_WIDTH /(float) WINDOW_HEIGHT;
	aspectRatio = 1;
	view.setCenter(sf::Vector2f(WINDOW_WIDTH/4, WINDOW_HEIGHT/4)); // divide by 4 just to get a good size
	view.setSize(sf::Vector2f(WINDOW_WIDTH/2 + BOARDER_SIZE * aspectRatio, WINDOW_HEIGHT/2 + BOARDER_SIZE)); // divide by 2 just to get a good size
	window.setView(view); // apply the changes made to the view to the current window!
}




