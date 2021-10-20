#include "Game.h"
#include <iostream> // Needed for std::cout


Game::Game():
 currentBoard()

//,currentStone(Stone::color::BLACK,0,0) //TODO Dontt do this here, it should just be empty or some default side and position then we set it later. depending on whos turn and location.
{
    // Create board object with current board.
    //m_stonePos1d.resize(currentBoard.getCurrentBoardSize());
     m_stonePos1d.reserve(currentBoard.getCurrentBoardSize()* currentBoard.getCurrentBoardSize());
    //stonePositions.resize(currentBoard.getCurrentBoardSize()); // FIx this for 2d vector
    //m_stonePos2d.resize(currentBoard.getCurrentBoardSize()); // THis works but 2d version dosnt
    //stonePositions.resize(currentBoard.getCurrentBoardSize(), std::vector<Stone>(currentBoard.getCurrentBoardSize()));

    //Load Stone texture
    m_textures.load(TextureHolder::ID::Stone, "Sprites/white_black.png");
    
    // Fill the vector with "NO_STONE" objects. (same functionality as the .resize() cmd.
    for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++)
    {
        for (int col = 0; col < currentBoard.getCurrentBoardSize(); col++)
        {
            m_stonePos1d.push_back(Stone(m_textures,Stone::COLOR::NO_STONE, col, row));
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
                std::cout << "the right button was pressed" << std::endl;
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
    //createStone(Stone::COLOR::BLACK, event.mouseButton.x, event.mouseButton.y);
    createStone(Stone::COLOR::BLACK, 40, 10);

}

void Game::createStone(Stone::COLOR side, int x, int y)
{
    //Stone newStone(&m_pieceTextures, side, x, y); // Do I just want to send a reference to this object here?

    //Stone newStone(&m_textures, side, x, y); ///////////// NEXT step is to get the correct texture here. I think I need to do m_textures -> but im too tired now.

    m_stonePos1d[75].setSide(side);
    m_stonePos1d[75].setSprite(side);
    std::cout << "This is the X position of the stone at Index 75:" << m_stonePos1d[75].getLocation().getx() << std::endl;

    //// Copy newly created stone into StonePosition vector.
    ////stonePositions[3][3] = newStone;
    ////stonePositions[1][1] = newStone;

    //m_stonePos1d[1] = newStone;

    ////Stone newNewStone(Stone::WHITE, 10, 10); 
    ////stonePos2d[2] = newNewStone;

    //If I use stonePos1d.reserv to increase the size of the vector I have to use pushback instead to add my Stones
    //use m_stonePos1d.push_back(Stone(&m_pieceTextures, side, x, y)); instead of what you're currently doing 




}

void Game::drawBoard(sf::RenderWindow& window)
{
    //Board currentBoard; // 0 means 9x9 board, change later so the player can specify board size from menu buttons
    window.draw(currentBoard.getBoard()); //M�ste f� in Board h�r p� n�got s�tt
}

void Game::drawStones(sf::RenderWindow& window)
{
    //window.draw(currentStone.getStone());
     //Loop through all the stones in the stonePosition vector and draw them.
    //for (int row = 0; row < currentBoard.getCurrentBoardSize(); row++)
    //{
    //    // another for loop going thorugh the y axis
    //    for (int col = 0; col < currentBoard.getCurrentBoardSize(); col++)
    //    {


    //        if (m_stonePos1d[row].getSide() != Stone::NO_STONE) ////////////////////////////////////////////////////////////77
    //        {
    //            window.draw(m_stonePos1d[row].getStone());
    //        }
    //        window.draw(m_stonePos1d[row][col].getStone());
    //    }
    //}

    window.draw(m_stonePos1d[75].getStoneSprite());
}





