#include "Board.h"

Board::Board(BOARDSIZE boardSize) :
	m_board()
,   m_boardTexture()
,   m_boardTextureSize()
,   m_boardSize(BOARD_19x19)


{
	m_boardSize = boardSize;
	selectBoardSize(boardSize);
}



void Board::selectBoardSize(BOARDSIZE boardSize)
{
	if (boardSize == BOARD_9x9) // 9x9_BOARD == 1
	{
		//create 9x9 board texture
		m_boardTexture.loadFromFile("Sprites/9x9_board.png");
		m_boardTextureSize = m_boardTexture.getSize();
		m_board.setSize(sf::Vector2f(m_boardTextureSize)); // Convert sf::Vector2u to sf::Vector2f before setting the size.
		m_board.setTexture(&m_boardTexture);
	}
	else if (boardSize == BOARD_13x13) //13x13_BOARD == 2
	{
		//create 13x13 board texture
	}
	else if (boardSize == BOARD_19x19) // 19x19_BOARD == 3
	{
		// create 19x19 board texture
	}
	else
	{
		//Invalid board size.
	}
}


sf::RectangleShape Board::getBoard()
{
	return m_board;
}

BOARDSIZE Board::getCurrentBoardSize()
{
	return m_boardSize;
}

sf::Vector2u Board::getBoardPixelSize()
{
	return m_boardTextureSize;
}
