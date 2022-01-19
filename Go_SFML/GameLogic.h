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
	int removeDeadStones(Stone::COLOR side, int boardSize, std::vector<std::vector<Stone>>& stonePositions2d,int checkSuicide);
	bool isKo(Stone::COLOR side,int boardSize, std::vector<std::vector<Stone>>& stonePositions2d);
	void setKoCoords();
	bool checkKoCoordsSameAsCurrentMove(sf::Vector2i coords);
	void resetKoCoords();
	bool checkForSuicideMove(Stone::COLOR side, int boardSize, std::vector<std::vector<Stone>>& stonePositions2d, sf::Vector2i currentMove);
	void updateScore(int nrOfDeadStones, Stone::COLOR side);
	int getBlackScore();
	int getWhiteScore();
	// Will fill the connecting area of the coords x,y with the color of side.
	bool floodFillArea(Stone::COLOR TargetSide, Stone::COLOR replacmentSide, std::vector<std::vector<Stone>>& stoneVector, std::vector<std::vector<Stone>>& ScoreStoneVector, int x, int y);
	void resetVisitedArray(int boardSize);
	void addTerritoryScore(Stone::COLOR side, int scoreToAdd);
	void setWinner(); // Saves the side with highest score.
	Stone::COLOR getWinner();


	enum GameState
	{
		TitleScreen,
		GamePlay,
		ScoreCounting,
		PresentWinner
	};

private:

	// Methods
	bool isInsideArea(int x1, int y1, int x2,
		int y2, int x, int y);
	bool aliveStoneCheck(Stone::COLOR side, std::vector<std::vector<Stone>>& stonePositions2d, int x, int y);

	
	// Member variables
	Stone::COLOR m_currentSide;
	int m_currentBoardSize;
	//sf::Vector2i possibleKoPos;

	struct koData
	{
		sf::Vector2i possibleKoPos; // the position of the single dead stone.
		sf::Vector2i certainKoPos; // The position of the singel dead stone.
		int nrOfDiedStones = 0;
		bool oneStoneDied = false;
		
	} dataKo;

	enum{ MAX_BOARD_SIZE = 19 };

	bool m_visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { false };
	// Keeps track of what stones are considered dead in the "check dead stones logic" 
	bool m_deadStones[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { false };
	// keep track of Ko location;
	sf::Vector2i currentKoPos;
	int m_blackScore;
	int m_whiteScore;

	int m_blackTerritoryScore;
	int m_whiteTerritoryScore;

	Stone::COLOR m_winner;


};

