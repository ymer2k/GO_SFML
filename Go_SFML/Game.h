#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Stone.h"
#include "Textures.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "GameLogic.h"
#include "TextStrings.h"
#include "Command.h"
#include "PlaceStoneCommand.h"
#include "GameLogic.h"
#include <memory>
#include "BaseSprite.h"



//This class Should do player interactions with the game


class Game
{


public:
	Game();
	// Function that controls interacting with the game world (mouse clicks, close window etc. This runs every cycle)
	bool interact(sf::RenderWindow & window);
	// Function that draws Objects
	void drawGame(sf::RenderWindow& window);
	// Function that deals with the logic of making a move (getting the new stone in the exact right position etc)
	// (Game logic should make call this function after it checks if it is a valid move or not)
	// should call createStone at the end.
	void makeMove(Stone::COLOR);
	// This function updates the game
	void update(sf::RenderWindow& window,GameLogic& GameState);
	//Draws text to the game.


	// Used to find the right text in m_textvector
	enum TEXTINDEX
	{
		BLACK,
		WHITE,
		SCORING_PHASE,
		WINNER,
		PLAY_AGAIN
	};

private:
	// Function that draws the board
	void drawBoard(sf::RenderWindow& window);
	// Function to draw Stones
	void drawStones(sf::RenderWindow& window);
	// Function to draw Stones after Game is finished and we do scoring
	void drawStonesScoring(sf::RenderWindow& window);
    // Function to create new stone objects ( with position and side and save into the vector)
	void createStone(Stone::COLOR side, int x, int y);
	// Function to update the game score.
	void updateTextScore(GameLogic& GameState);
	// Function to to handle all game board related things like clicks, moves, rules, points etc
	void handleMakingMoveLogic(sf::RenderWindow& window, GameLogic& GameState);
	// Function to handle pass functionality
	void handlePassFunctionality(GameLogic& GameState);
	// Function that handle Done button functionality
	void handleDoneButtonFunctionality(GameLogic& GameState);
	// Draw text
	void drawText(sf::RenderWindow& window);
	// update winner text
	void updateWinnerText(GameLogic& GameState);
	// initialize the stone vectors (depends on board size)
	void initStoneVectors();
	// Load, set texture and position of BaseSprite objects
	// Takes a reference to the BaseSprite we want to load
	void initBaseSpriteObject(BaseSprite & sprite,const std::string& filename, TextureHolder::ID id, float scale, sf::Vector2i pos);
	// Initilise all text objects
	void initText();
	// handle board size button functionality
	bool handleBoardSizeButtonFunctionality();
	// choose BoardSizeFunctionality
	//void handleBoardSizeFunctionality()




	// Member variables

	Board m_currentBoard;
	// use gamelogic to call funcitons in gamelogic that will return stuff I need. forexample yes it was a valid move etc.
	// the functions I call will have to take in Game object to get the info it needs to calculate teh stuff to return. And maybe Board too.
	GameLogic gameLogic;

	//Stone vector;
	std::vector<std::vector<Stone>> m_stonePositions2d;

	// Scoring Stone Vector
	std::vector<std::vector<Stone>> m_scoreStonePositions2d;


	//BaseSprite Pass button
	BaseSprite m_passButton;

	//BaseSprite pass icon
	BaseSprite m_passIcon;

	//BaseSprite yesButton
	BaseSprite m_yesButton;

	BaseSprite m_noButton;

	//BaseSprite Done button
	BaseSprite m_doneButton;

	BaseSprite m_smallStone;

	BaseSprite m_9x9Button;
	BaseSprite m_13x13Button;
	BaseSprite m_19x19Button;


	TextureHolder m_textures;// Later have input arguemnts that decides which type of texture to retrive. Game should handle all Texture objects (long Scope)
	//Textures m_boardTexture(Textures::TextureType::BOARD) Like this <-

	FontHolder m_fonts;
	//Hold all Text objects
	std::vector<TextStrings> m_textVector;  // size for 10 text objects
	// input commands
	Command* leftMouseButton = new PlaceStoneCommand(); //Change to unique_ptr
	//std::unique_ptr<Command> leftMouseButton(new Command());

	// last click converted to world position.
	sf::Vector2f m_worldMousePos;

	// flag if player has passed or not. SHould be moved to the GameLogic class
	bool m_blackPassed; 
	bool m_whitePassed;
	Stone::COLOR m_currentside;




	GameLogic::GameState m_currentGameState;


	
};

