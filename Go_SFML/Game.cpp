#include "Game.h"
#include <iostream> // Needed for std::cout
#include <cmath>


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

//Command * Game::interact(sf::RenderWindow & window)
bool Game::interact(sf::RenderWindow & window)
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
                std::cout << "Pixel System mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "Pixel System mouse y: " << event.mouseButton.y << std::endl;

                //For now just hard code to get the basics working like drawing a stone on the coords im clicking.

                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                m_worldMousePos = window.mapPixelToCoords(mousePos);

                //createStone(Stone::COLOR::BLACK, std::round(event.mouseButton.x), std::round(event.mouseButton.y));
                //createStone(Stone::COLOR::BLACK, std::round(m_worldMousePos.x), std::round(m_worldMousePos.y));

                std::cout << "Coords System mouse x: " << std::round(m_worldMousePos.x) << std::endl;
                std::cout << "Coords System mouse y: " << std::round(m_worldMousePos.y) << std::endl;

                //Implement commands after I get basic stone drawing to work AND when I figure out how to seperate game logic and input 
                //Command* leftMouseButton = new PlaceStoneCommand(sf::Vector2f(event.mouseButton.x, event.mouseButton.y),Stone::COLOR::BLACK); //get current side from gameLogic class.
                //leftMouseButton->execute();

                //

                // return 

                // This loop should not handle any mouse click stuff just call a "mouseLeftClick" function here and that functino will handle everything.
                // It will check if we pressed a button (and handle that) or if we pressed the board (and then call a function to check if the move is ok)
                // send in mouseclick into gameLogic function to check if, 1st the click was made on the board and if yes if the square is free.
                //  Also send a const reference to
                // m_stonePositions2d to check if the position is free, if free return an enum saying which side made the move (and in turn which stone color)
                // this info will be passed to the createStone function. If not free it will return an enum saying not free.
                return true;
            }
        }
        else
            return false;

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

void Game::update(sf::RenderWindow& window, GameLogic& GameState)
{
    //Create gameLogic
    //Get the corresponding Board Index of the click.
    sf::Vector2i clickedBoardPositionIndex(GameState.findClickedBoardPositionIndex(m_worldMousePos, currentBoard, m_stonePositions2d[0][0].getStonePixelSize()));

    //Return if clicked outside of the Board, //Later we will have buttons like Resign etc so then this would have to change.
    if (clickedBoardPositionIndex.x == -1)
    {
        return; //Clicked outside of the board.
    }


    bool isSquareEmpty = GameState.checkIfSquareEmpty(m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]);

    //Put into a method func addMoveToVector().
    if (isSquareEmpty)
    {
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(GameState.getCurrentSide());
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSprite(GameState.getCurrentSide());
        sf::Vector2u stoneTextureSize(m_stonePositions2d[0][0].getStonePixelSize());
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]
            .setPosition(stoneTextureSize.x * clickedBoardPositionIndex.x, stoneTextureSize.y * clickedBoardPositionIndex.y);
        //Change sides after "valid" move
        GameState.changeSide();
    }

    //func checkForCapture    or func checkLiberties

}

void Game::drawText()
{

}

void Game::createStone(Stone::COLOR side, int x, int y)
{
    int Xindex = x / (currentBoard.getBoardPixelSize().x / currentBoard.getCurrentBoardSize());
    int Yindex = y / (currentBoard.getBoardPixelSize().x / currentBoard.getCurrentBoardSize());
    
    //Sort away clicks that are outside of the board.
    if (Xindex > currentBoard.getCurrentBoardSize()-1 || Yindex > currentBoard.getCurrentBoardSize()-1)
        return;

    std::cout << "Xindex: " << Xindex << std::endl;
    std::cout << "Yindex " << Yindex << std::endl;

    m_stonePositions2d[Xindex][Yindex].setSide(side);
    m_stonePositions2d[Xindex][Yindex].setSprite(side);
    m_stonePositions2d[Xindex][Yindex].setPosition(x, y);



    //m_stonePositions2d[2][7].setSide(side);
    //m_stonePositions2d[2][7].setSprite(side);
    //m_stonePositions2d[2][7].setPosition(x, y);

    //m_stonePositions2d[4][4].setSide(side);
    //m_stonePositions2d[4][4].setSprite(side);
    //m_stonePositions2d[4][4].setPosition(80, 80);
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





