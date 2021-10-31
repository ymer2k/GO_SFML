#include "Render.h"
#include "Board.h"


Render::Render() : //Constructor
	WINDOW_WIDTH(800)
	,WINDOW_HEIGHT(600)
	,BOARDER_SIZE(5)
{
	initializeWorld();
}

void Render::initializeWorld()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Go"); // the create  function is used when we create the window AFTER initilization.
	view = window.getView();
	// almost everything here should be member variables I guess Textures, sprites, shapes, fonts, etc.
	float aspectRatio =(float) WINDOW_WIDTH /(float) WINDOW_HEIGHT;
	view.setCenter(sf::Vector2f(WINDOW_WIDTH/4, WINDOW_HEIGHT/4)); // divide by 4 just to get a good size
	view.setSize(sf::Vector2f(WINDOW_WIDTH/2 + BOARDER_SIZE * aspectRatio, WINDOW_HEIGHT/2 + BOARDER_SIZE)); // divide by 2 just to get a good size
	window.setView(view); // apply the changes made to the view to the current window!
}




