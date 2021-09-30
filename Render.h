#pragma once
#include <SFML/Graphics.hpp>

// The renderer, should handle rendering objects and the window etc.
// Render takes in objects to be drawn in the window.

class Render
{


public:
	Render(); // Constructor
	// Member functions


	// Member variables
	const int BOARD_SIZE = 9;
	sf::RenderWindow window;
	sf::View view;

	// OBS apparently variables get intilialized (get a value) in the init list in the order that they are declared here. So since the window uses WINDOW_WIDTH
	// But window is above WINDOW_WIDTH here then in the init list (if I had window in the init list) It would have been initialized with probably
	// garbash values of WINDOW_WIDTH. SO do fix that, either have those variables higher up here than sf::RenderWindow window. Or just create the window (with the window.create() function)
	// in the constructor AFTER the WINDOW_WIDTH variables have been initialized.
private:
	// Member functions
	void initializeWorld();

	// Member variables
	const int BORDER_X;
	const int BORDER_Y;
	const int WINDOW_WIDTH; // Could also in the future pass this as arguments to render in the constructor as input arguments to decied or change resolution :)
	const int WINDOW_HEIGHT;
	const int BOARDER_SIZE;
	
};

