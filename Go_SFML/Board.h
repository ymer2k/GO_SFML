#pragma once
#include <SFML/Graphics.hpp>

// Takes care of board sizes etc things related to board.

// Maybe change to constants
enum BOARDSIZE
{
	BOARD_9x9 = 9,
	BOARD_13x13 = 13,
	BOARD_19x19 = 19
};

class Board
{


public:
	//Board(BOARDSIZE boardSize = BOARDSIZE::BOARD_9x9); // Constructor //Maybe in the constructor have input arguments be board size.
	Board();


	sf::RectangleShape getBoard();
	BOARDSIZE getCurrentBoardSize();
	sf::Vector2u getBoardPixelSize();
	void selectBoardSize(BOARDSIZE boardSize);



private:
	// member functions


	// member variables
	sf::Texture m_boardTexture;
	sf::RectangleShape m_board;
	sf::Vector2u m_boardTextureSize;
	BOARDSIZE m_boardSize;


};

