#include "Render.h"


Render::Render() : //Constructor
	 BORDER_X(0)
	,BORDER_Y(0)
	,window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Go")
	,view(window.getView())
	,WINDOW_WIDTH(800)
	,WINDOW_HEIGHT(600)
	,BOARDER_SIZE(5)
	

{
	initializeWorld();
}

void Render::initializeWorld()
{

	// almost everything here should be member variables I guess Textures, sprites, shapes, fonts, etc.
	int aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
	view.setCenter(sf::Vector2f(WINDOW_WIDTH/4, WINDOW_HEIGHT/4));
	view.setSize(sf::Vector2f(WINDOW_WIDTH/2 + BOARDER_SIZE * aspectRatio, WINDOW_HEIGHT/2 + BOARDER_SIZE));

}


