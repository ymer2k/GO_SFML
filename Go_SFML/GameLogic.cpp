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
	m_currentSide(Stone::COLOR::BLACK)
	, m_currentBoardSize(0)
	, m_blackCaptureScore(0)
	, m_whiteCaptureScore(0)
	, m_blackTerritoryScore(0)
	, m_whiteTerritoryScore(0)
	, m_winner(Stone::COLOR::NO_STONE)
{

}

void GameLogic::rungame()
{
}

sf::Vector2i GameLogic::findClickedBoardPositionIndex(sf::Vector2f worldMousePos, Board& currentBoard, sf::Vector2u stoneTexturePixelSize) //Only have board size instead of board object as input argument
{
	m_currentBoardSize = (int) currentBoard.getCurrentBoardSize();
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
	if (stone.getSide() == Stone::COLOR::NO_STONE)
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
	m_currentSide = m_currentSide == Stone::COLOR::BLACK ? Stone::COLOR::WHITE : Stone::COLOR::BLACK;
}

void GameLogic::setSide(Stone::COLOR side)
{
	m_currentSide = side;
}

bool GameLogic::isInsideArea(int x1, int y1, int x2, int y2, int x, int y)
{
	//x1 and y1 is top left corner of a rectangle and x2 y2 is the bottom right. x,y is the point.
	if (x > x1 and x < x2 and y > y1 and y < y2)
		return true;

	return false;
}

int GameLogic::removeDeadStones(Stone::COLOR side, int boardSize, std::vector<std::vector<Stone>>& stonePositions2d,int checkSuicide)
{
	
	int deadStones[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };

	

	//Check the stones NOT from the side that just made a move. ( Example: if black made a move, check if any white stones died)
	// Loop through all positions on the board and skip empty and not current side stone.
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
		{
			if (stonePositions2d[x][y].getSide() != side)
			{
				continue;
			}
			//Reset the m_visited vector to all false (loop through all positions)
			for (int x = 0; x < boardSize; x++) for (int y = 0; y < boardSize; y++) m_visited[x][y] = false;
			if(!aliveStoneCheck(side, stonePositions2d, x, y))
			{
				//Add to coord to deadStonesVector
				deadStones[x][y] = 1;
			}
		}
	//Loop through all positions and look for at deadStonesVector for dead stones. if dead, change the corresponding index
	// in stonePositions2d to no_Stone.
	int nrOfDeadStones = 0;
	for (int x = 0; x < boardSize; x++) for (int y = 0; y < boardSize; y++)
	{
		if (deadStones[x][y] == 1)
		{
			nrOfDeadStones++;
			//possibleKoPos.x = x;
			//possibleKoPos.y = y;
			dataKo.possibleKoPos.x = x;
			dataKo.possibleKoPos.y = y;

			stonePositions2d[x][y].setSide(Stone::COLOR::NO_STONE);
		}
	}
	if (nrOfDeadStones == 1)
	{
		dataKo.oneStoneDied = true;
		// Save the position of the dead stone so we can revert it IF it turns out to be a KO move.
	}

	return nrOfDeadStones;
}

bool GameLogic::isKo(Stone::COLOR side, int boardSize, std::vector<std::vector<Stone>>& stonePositions2d)
{
	bool retVal = false;
	int x = dataKo.possibleKoPos.x;
	int y = dataKo.possibleKoPos.y;
	if (dataKo.oneStoneDied) // There can only be KO if ONE single stone died.
	{


		//Check if surrounding stones are of same color as the player that made a move this turn. 
		//Also make sure we are not out of bounds! being out of bounds is same as being surrounded by a stone on that side
		retVal = ((x - 1) < 0) || (side == stonePositions2d[x - 1][y].getSide());
		retVal &= ((x + 1) > boardSize - 1) || (side == stonePositions2d[x + 1][y].getSide());
		retVal &= ((y - 1) < 0) || (side == stonePositions2d[x][y - 1].getSide());
		retVal &= ((y + 1) > boardSize - 1) || (side == stonePositions2d[x][y + 1].getSide());

		dataKo.oneStoneDied = false; //reset
		return  retVal;

	}

	dataKo.oneStoneDied = false; //reset
	return false;
}

void GameLogic::setKoCoords()
{
	dataKo.certainKoPos = dataKo.possibleKoPos;
}

bool GameLogic::checkKoCoordsSameAsCurrentMove(sf::Vector2i coords)
{
	if (coords == dataKo.certainKoPos)
		return true;

	return false;
}

void GameLogic::resetKoCoords()
{
	dataKo.certainKoPos.x = -1;
	dataKo.certainKoPos.y = -1;
}

bool GameLogic::checkForSuicideMove(Stone::COLOR side, int boardSize, std::vector<std::vector<Stone>>& stonePositions2d, sf::Vector2i currentMove)
{
	// Temporarley make the move in stonePositions2d
	stonePositions2d[currentMove.x][currentMove.y].setSide(side);

	int deadStones[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };
	//Reset the m_visited vector to all false (loop through all positions)
	for (int x = 0; x < boardSize; x++) for (int y = 0; y < boardSize; y++) m_visited[x][y] = false;
	if (!aliveStoneCheck(side, stonePositions2d, currentMove.x, currentMove.y))
	{
		//Remove the temp move before we return
		stonePositions2d[currentMove.x][currentMove.y].setSide(Stone::COLOR::NO_STONE);
		return true;
	}
	else
	{
		//remove the temp move before we return
		stonePositions2d[currentMove.x][currentMove.y].setSide(Stone::COLOR::NO_STONE);
		return false;
	}
		
}

void GameLogic::updateScore(int nrOfDeadStones, Stone::COLOR side)
{
	if (side == Stone::COLOR::BLACK)
	{
		m_blackCaptureScore += nrOfDeadStones;
		std::cout << "Black: " << m_blackCaptureScore << std::endl;

	}
	else
	{
		m_whiteCaptureScore += nrOfDeadStones;
		std::cout << "White: " << m_whiteCaptureScore << std::endl;
	}

}

int GameLogic::getBlackScore()
{
	return m_blackCaptureScore+m_blackTerritoryScore;
}

int GameLogic::getWhiteScore()
{
	return m_whiteCaptureScore+m_whiteTerritoryScore;
}



bool GameLogic::aliveStoneCheck(Stone::COLOR side, std::vector<std::vector<Stone>>& stonePositions2d, int x, int y)
{
	// Side is the color we look if its dead or not.

	//Check if out of bounds.
	if (x > m_currentBoardSize - 1 || x < 0 || y > m_currentBoardSize -1 || y < 0)
		return false;

	if (m_visited[x][y])
		return false; //If already visited skip
	m_visited[x][y] = true;

	if (stonePositions2d[x][y].getSide() == Stone::COLOR::NO_STONE)
		return true; // No stone means it has a liberty and thus alive.

	if (stonePositions2d[x][y].getSide() != side)
		return false; //That x,y coord does NOT have a liberty (or own stone) so return false.

	//recursive search for more stones of "side"
	bool retVal = aliveStoneCheck(side, stonePositions2d, x - 1, y);
	retVal |= aliveStoneCheck(side, stonePositions2d, x + 1, y);
	retVal |= aliveStoneCheck(side, stonePositions2d, x, y - 1);
	retVal |= aliveStoneCheck(side, stonePositions2d, x, y + 1);
	return retVal;
}

bool GameLogic::floodFillArea(Stone::COLOR TargetSide,
	Stone::COLOR replacmentSide,
	std::vector<std::vector<Stone>>& stoneVector,
	std::vector<std::vector<Stone>>& ScoreStoneVector,
	int x, int y)
{
	// TargetSide is the side we look for and change to a different side.
	// replacmentSide is the side we change the TargetSide to.
	if (x > m_currentBoardSize - 1 || x < 0 || y > m_currentBoardSize - 1 || y < 0)
		return false;

	if (m_visited[x][y])
		return false; //If already visited skip
	m_visited[x][y] = true;

	// if we already changed color or found same color then return
	//if (stoneVector[x][y].getSide() == replacmentSide)
	//	return false;

	if (stoneVector[x][y].getSide() != TargetSide)
		return false;


	// Have an if statment that if at the coords of the replacmentstone has the same type of stone in the normal stone vector then just return 
	// Do this to avoid drawing same color area on same color stones.
	if (replacmentSide == stoneVector[x][y].getSide() && replacmentSide != Stone::COLOR::NO_STONE)
		return false; //Same color stone as replacmentStone.

	// add the replacmentside to the scorestonevector
	ScoreStoneVector[x][y].setSide(replacmentSide);
	// quick hack to just move the origin of the stons to the center of the stone instead of the top left corner (makes scaling easier later)
	float originOffset = 9.5;
	ScoreStoneVector[x][y].setOrigin(originOffset, originOffset);
	//
	ScoreStoneVector[x][y]
		.setPosition(19 * x + originOffset, 19 * y + originOffset);
	ScoreStoneVector[x][y].setSprite(replacmentSide);


	//recursive search for more stones of "side"
	bool retVal = floodFillArea(TargetSide, replacmentSide, stoneVector,ScoreStoneVector, x - 1, y);
	retVal |= floodFillArea(TargetSide, replacmentSide, stoneVector, ScoreStoneVector, x + 1, y);
	retVal |= floodFillArea(TargetSide, replacmentSide, stoneVector, ScoreStoneVector, x, y - 1);
	retVal |= floodFillArea(TargetSide, replacmentSide, stoneVector, ScoreStoneVector, x, y + 1);
	return retVal;

	return false;
}

void GameLogic::resetVisitedArray(int boardSize)
{
	//Reset the m_visited vector to all false (loop through all positions)
	for (int x = 0; x < boardSize; x++) for (int y = 0; y < boardSize; y++) m_visited[x][y] = false;
}

void GameLogic::addTerritoryScore(Stone::COLOR side, int scoreToAdd)
{
	if (side == Stone::COLOR::BLACK)
	{
		m_blackTerritoryScore = scoreToAdd;
	}
	else if (side == Stone::COLOR::WHITE)
		m_whiteTerritoryScore = scoreToAdd;
}

void GameLogic::setWinner()
{

	if ((m_blackCaptureScore + m_blackTerritoryScore) > (m_whiteCaptureScore + m_whiteTerritoryScore))
	{
		m_winner = Stone::COLOR::BLACK;
	}
	else if ((m_blackCaptureScore + m_blackTerritoryScore) < (m_whiteCaptureScore + m_whiteTerritoryScore))
	{
		m_winner = Stone::COLOR::WHITE;
	}
	else
		m_winner = Stone::COLOR::NO_STONE;
	
}

Stone::COLOR GameLogic::getWinner()
{
	return m_winner;
}

void GameLogic::resetEverything()
{
	m_blackCaptureScore = 0;
	m_whiteCaptureScore = 0;
	m_blackTerritoryScore = 0;
	m_whiteTerritoryScore = 0;
	m_winner = Stone::COLOR::NO_STONE;
}

void GameLogic::revertCapturedStone(std::vector<std::vector<Stone>>& stonePositions2d, Stone::COLOR capturedStoneSide)
{
	stonePositions2d[dataKo.possibleKoPos.x][dataKo.possibleKoPos.y].setSide(capturedStoneSide);
	
}
