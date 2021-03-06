#include "Board.h"

//Board::Board(BOARDSIZE boardSize) :
Board::Board():
	m_board()
,   m_boardTexture()
,   m_boardTextureSize()
,   m_boardSize(BOARDSIZE::BOARD_19x19)
{
}

void Board::selectBoardSize(BOARDSIZE boardSize)
{
	if (boardSize == BOARDSIZE::BOARD_9x9)
	{
		//create 9x9 board texture
		m_boardTexture.loadFromFile("Sprites/9x9_board.png");
		m_boardTextureSize = m_boardTexture.getSize();
		m_board.setSize(sf::Vector2f(m_boardTextureSize)); // Convert sf::Vector2u to sf::Vector2f before setting the size.
		m_board.setTexture(&m_boardTexture);
		m_boardSize = BOARDSIZE::BOARD_9x9;
		// Set m_currentBoardScale // Get this in the Game class to adjust for a scale difference in bordsize.
	}
	else if (boardSize == BOARDSIZE::BOARD_13x13)
	{
		//create 13x13 board texture
		m_boardTexture.loadFromFile("Sprites/13x13_board.png");
		m_boardTextureSize = m_boardTexture.getSize();
		m_board.setSize(sf::Vector2f(m_boardTextureSize)); // Convert sf::Vector2u to sf::Vector2f before setting the size.
		m_board.setTexture(&m_boardTexture);
		m_boardSize = BOARDSIZE::BOARD_13x13;
		// Set m_currentBoardScale // Get this in the Game class to adjust for a scale difference in bordsize.
	}
	else if (boardSize == BOARDSIZE::BOARD_19x19)
	{
		m_boardTexture.loadFromFile("Sprites/19x19_board.png");
		m_boardTextureSize = m_boardTexture.getSize();
		m_board.setSize(sf::Vector2f(m_boardTextureSize)); // Convert sf::Vector2u to sf::Vector2f before setting the size.
		m_board.setTexture(&m_boardTexture);
		//m_board.setScale(0.7, 0.7);
		m_boardSize = BOARDSIZE::BOARD_19x19;
		// Set m_currentBoardScale // Get this in the Game class to adjust for a scale difference in bordsize.
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
