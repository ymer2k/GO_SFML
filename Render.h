#pragma once
#include <SFML/Graphics.hpp>

class Render
{

public:
	Render(); // Constructor
	const int BOARD_SIZE = 9;
	sf::RenderWindow window;
	sf::View view;


private:
	// Member functions
	void initializeWorld();

	// Member variables

	
	const int BORDER_X;
	const int BORDER_Y;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const int BOARDER_SIZE;
	//sf::Vector3i THStoneLocations[BOARD_SIZE][BOARD_SIZE]; // stores the pices locations. Have to use 3i because i want to save 3d coords into this vector. x, y and side :)
	
};

