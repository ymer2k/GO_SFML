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
	void drawText();

private:
	// Function that draws the board
	void drawBoard(sf::RenderWindow& window);
	// Function to draw Stones
	void drawStones(sf::RenderWindow& window);
	 // Function to create new stone objects ( with position and side and save into the vector)
	void createStone(Stone::COLOR side, int x, int y);
	// Function to update the game score.
	void UpdateTextScore(GameLogic& GameState);




	// Member variables
	sf::Event event;
	Board m_currentBoard;
	// use gamelogic to call funcitons in gamelogic that will return stuff I need. forexample yes it was a valid move etc.
	// the functions I call will have to take in Game object to get the info it needs to calculate teh stuff to return. And maybe Board too.
	GameLogic gameLogic;

	//Stone currentStone;
	std::vector<std::vector<Stone>> m_stonePositions2d;

	TextureHolder m_textures;// Later have input arguemnts that decides which type of texture to retrive. Game should handle all Texture objects (long Scope)
	//Textures m_boardTexture(Textures::TextureType::BOARD) Like this <-

	FontHolder m_fonts;
	//Hold all Text objects
	std::vector<TextStrings> m_textVector;  // size for 10 text objects
	// input commands
	Command* leftMouseButton = new PlaceStoneCommand(); //Change to unique_ptr
	//std::unique_ptr<Command> leftMouseButton(new Command());

	sf::Vector2f m_worldMousePos;



	
};

