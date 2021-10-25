#include "Game.h"
#include <iostream> // Needed for std::cout


Game::Game():
 currentBoard()

//,currentStone(Stone::color::BLACK,0,0) //TODO Dontt do this here, it should just be empty or some default side and position then we set it later. depending on whos turn and location.
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
        
    // Fill the vector with "NO_STONE" objects. (same functionality as the .resize() cmd.
    for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++)
    {
        for (int col = 0; col < currentBoard.getCurrentBoardSize(); col++)
        {
            m_stonePositions2d[row].push_back(Stone(m_textures, Stone::COLOR::NO_STONE, col, row)); 
        }
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
    createStone(Stone::COLOR::BLACK, 40, 10);

}

void Game::createStone(Stone::COLOR side, int x, int y)
{
    m_stonePositions2d[1][1].setSide(side);
    m_stonePositions2d[1][1].setSprite(side);
    m_stonePositions2d[1][1].setPosition(x, y);
    }

void Game::drawBoard(sf::RenderWindow& window)
{
    // 0 means 9x9 board, change later so the player can specify board size from menu buttons
    window.draw(currentBoard.getBoard()); //Måste få in Board här på något sätt. Maybe Game has a parameter that takes in boardsize when it is created.
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





