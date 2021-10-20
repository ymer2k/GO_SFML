#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Stone.h"
#include "Textures.h"
#include "TextureHolder.h"





//This is Current Game. Keeps stuff like mouseclicks? Or something like that.


class Game
{


public:
	Game();
	// Function that controls interacting with the game world (mouse clicks, close window etc. This runs every cycle)
	void interact(sf::RenderWindow & window);
	// Function that draws Objects
	void drawGame(sf::RenderWindow& window);
	// Function that deals with the logic of making a move (getting the new stone in the exact right position etc)
	// (Game logic should make call this function after it checks if it is a valid move or not)
	// should call createStone at the end.
	void makeMove(Stone::COLOR);

private:
	// Function that draws the board
	void drawBoard(sf::RenderWindow& window);
	// Function to draw Stones
	void drawStones(sf::RenderWindow& window);
	 // Function to create new stone objects ( with position and side and save into the vector)
	void createStone(Stone::COLOR side, int x, int y);



	// Member variables
	sf::Event event;
	Board currentBoard;
	//Stone currentStone;
	//std::vector<std::vector<Stone>> stonePositions;
	std::vector<Stone> m_stonePos1d;
	//std::vector<int> ju(currentBoard.getCurrentBoardSize());

	Textures m_pieceTextures; // Later have input arguemnts that decides which type of texture to retrive. Game should handle all Texture objects (long Scope)
	//Textures m_boardTexture(Textures::TextureType::BOARD) Like this <-
	TextureHolder m_textures;
	
};

