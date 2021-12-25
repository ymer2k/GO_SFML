#include "GameLogic.h"
/*
This class should take care of things like;
deciding if a move is valid,
	- Stone already there
	- Suicide move
	- ko move (illegal recapture)
	- etc
translate a mouseclick to a real place on the board,
deciding if one or a group of stones are dead,
Count points when game is over, (this is quite difficult) because I think many programs
have AI that plays until there are no more moves
possible and calculates like that. But an easy way would be to just have the player mark dead
stones for themselves and if something is missing
they have to continue playing and fill in some stones.

*/ 
GameLogic::GameLogic():
	m_currentSide(Stone::BLACK)
{

}

void GameLogic::rungame()
{
}

sf::Vector2i GameLogic::findClickedBoardPositionIndex(sf::Vector2f worldMousePos, Board& currentBoard, sf::Vector2u stoneTexturePixelSize) //Only have board size instead of board object as input argument
{
	// Checks every square area on the board to find which square the mouse clicked in.
	for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++)
	{
		for (int col = 0; col < currentBoard.getCurrentBoardSize(); col++)
		{

			sf::Vector2i piecePos;
			piecePos.x = col * stoneTexturePixelSize.x;
			piecePos.y = row * stoneTexturePixelSize.y;
			int x2 = piecePos.x + stoneTexturePixelSize.x;
			int y2 = piecePos.y + stoneTexturePixelSize.y;

			if (isInsideArea(piecePos.x, piecePos.y, x2, y2, worldMousePos.x, worldMousePos.y))
			{
				//// TODO Move to a function in gameLogic that calls this vector?
				//if (THStoneLocations[col][row].z != 0) //If not empty
				//{
				//	//blank
				//}
				//else
				//{
				//	THStoneLocations[col][row] = piecePos;
				//	side == 2 ? side = 1 : side = 2;  // change sides.
				//}
				//StoneLocations[col][row] = piecePos; // stores the pices locations.

				sf::Vector2i retVal(col, row);
				return retVal;

			}

		}
	}
	//Clicked outside of Board
	return sf::Vector2i(-1, -1); //invalid value.
	
	
}

bool GameLogic::checkIfSquareEmpty(Stone stone)
{
	if (stone.getSide() == stone.NO_STONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Stone::COLOR GameLogic::getCurrentSide()
{
	return m_currentSide;
}

void GameLogic::changeSide()
{
	m_currentSide = m_currentSide == Stone::BLACK ? Stone::WHITE : Stone::BLACK;
}

bool GameLogic::isInsideArea(int x1, int y1, int x2, int y2, int x, int y)
{
	//x1 and y1 is top left corner of a rectangle and x2 y2 is the bottom right. x,y is the point.
	if (x > x1 and x < x2 and y > y1 and y < y2)
		return true;

	return false;
}
