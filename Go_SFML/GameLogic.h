#pragma once
#include "Board.h"
#include "Stone.h"

class GameLogic
{


public:
	GameLogic(); // Constructor

	// Methods
	void rungame(); // Runs the main game loop;
	// Member variables
	sf::Vector2i findClickedBoardPositionIndex(sf::Vector2f worldMousePos, Board & currentBoard, sf::Vector2u stoneTexturePixelSize);
	bool checkIfSquareEmpty(Stone stone);
	bool checkIfValidMove(); // Logic to check if we break any rules by placing here "checkIfSquareEmpty" should be places in this method
	void placeValidMoveInStoneVector(sf::Vector2i stoneIndex);
	Stone::COLOR getCurrentSide();
	void changeSide();


private:

	// Methods
	bool isInsideArea(int x1, int y1, int x2,
		int y2, int x, int y);

	// Member variables
	Stone::COLOR m_currentSide;

};

