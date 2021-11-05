#include "Game.h"
#include <iostream> // Needed for std::cout


Game::Game()
{

    //Load text font
    m_fonts.load(FontHolder::FontID::Ariel, "Fonts/ariblk.ttf");
    //Create and put text in array
    m_textVector.reserve(10);
    //m_textVector.emplace_back();
    //Text object(m_fonts, "test", sf::Color::Red, 20, sf::Text::Bold, sf::Vector2f(32, 3));
    //Text object("Jude");
    TextStrings object(m_fonts,"Test",sf::Color::Blue,30,sf::Text::Bold,sf::Vector2f(200,200));

    m_textVector.emplace_back(object);

    //Put this in a function (init Stones)
    //Load Stone texture
    m_textures.load(TextureHolder::ID::Stone, "Sprites/white_black.png");
    // resize the outer vector
    m_stonePositions2d.resize(currentBoard.getCurrentBoardSize());
    // resize in the inner vectors and fill every position with a Stone Object. (have to do all this because I dont have a default constructor)
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


    for (auto& value : m_textVector)
    {
        window.draw(value.getText());
    }
}

void Game::makeMove(Stone::COLOR side)
{   
    createStone(Stone::COLOR::WHITE, 40, 40);

}

void Game::update()
{
}

void Game::drawText()
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





