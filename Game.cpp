#include "Game.h"
#include <iostream> // Needed for std::cout


Game::Game():
 currentBoard()

{
    // Create board object with current board.

    //Load Stone texture
    m_textures.load(TextureHolder::ID::Stone, "Sprites/white_black.png");


     // resize the outer vector
     m_stonePositions2d.resize(currentBoard.getCurrentBoardSize());
     // resize in the inner vectors and fill every position with a Stone Object.
     for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++) 
     {
         m_stonePositions2d[row].resize(currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1));
     }
        
}

void Game::interact(sf::RenderWindow & window)
{
    while (window.pollEvent(event))
    {
        // Maybe use switch case instead. Add mouse click etc!
        if (event.type == sf::Event::Closed)
            window.close();


        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "the LEFT button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                // This loop should not handle any mouse click stuff just call a "mouseLeftClick" function here and that functino will handle everything.
                // It will check if we pressed a button (and handle that) or if we pressed the board (and then call a function to check if the move is ok)
                // send in mouseclick into gameLogic function to check if, 1st the click was made on the board and if yes if the square is free.
                //  Also send a const reference to
                // m_stonePositions2d to check if the position is free, if free return an enum saying which side made the move (and in turn which stone color)
                // this info will be passed to the createStone function. If not free it will return an enum saying not free.

            }
        }
        
        if (event.type == sf::Event::MouseButtonReleased)
        {
            //released = true;
        }
    }
}

void Game::drawGame(sf::RenderWindow& window)
{
    drawBoard(window);
    drawStones(window);
}

void Game::makeMove(Stone::COLOR side)
{   
    createStone(Stone::COLOR::WHITE, 40, 40);

}

void Game::update()
{
}

void Game::createStone(Stone::COLOR side, int x, int y)
{
    m_stonePositions2d[2][7].setSide(side);
    m_stonePositions2d[2][7].setSprite(side);
    m_stonePositions2d[2][7].setPosition(x, y);

    m_stonePositions2d[4][4].setSide(side);
    m_stonePositions2d[4][4].setSprite(side);
    m_stonePositions2d[4][4].setPosition(80, 80);
    }

void Game::drawBoard(sf::RenderWindow& window)
{
    // 0 means 9x9 board, change later so the player can specify board size from menu buttons
    window.draw(currentBoard.getBoard()); //M�ste f� in Board h�r p� n�got s�tt. Maybe Game has a parameter that takes in boardsize when it is created.
    // Gets board size from a menu click or something.
}

void Game::drawStones(sf::RenderWindow& window)
{
     //Loop through all the stones in the m_stonePositions2d vector and draw them.
    for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++)
    {
        // another for loop going thorugh the y axis
        for (int col = 0; col < currentBoard.getCurrentBoardSize(); col++)
        {


            if (m_stonePositions2d[row][col].getSide() != Stone::NO_STONE)
            {
                window.draw(m_stonePositions2d[row][col].getStoneSprite());
            }
            
        }
    }




}





