#include "Game.h"
#include <iostream> // Needed for std::cout
#include <cmath>
#include <string>


Game::Game()
   // : m_passButton(m_textures)
{

    //Load text font
    m_fonts.load(FontHolder::FontID::Ariel, "Fonts/slkscre.ttf");
    //Create and put text in array  
    sf::Vector2u boardTextureSize(m_currentBoard.getBoardPixelSize());
    TextStrings blackText(m_fonts,"BLACK: 0",sf::Color::White,10,sf::Text::Bold,sf::Vector2u(boardTextureSize.x/10, boardTextureSize.y*1.05));
    m_textVector.emplace_back(blackText);

    TextStrings whiteText(m_fonts, "WHITE: 0", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(boardTextureSize.x * 6 / 10, boardTextureSize.y * 1.05));
    m_textVector.emplace_back(whiteText);

    //Put this in a function (init Stones)
    //Load Stone texture
    m_textures.load(TextureHolder::ID::Stone, "Sprites/white_black.png");
    // resize the outer vector
    m_stonePositions2d.resize(m_currentBoard.getCurrentBoardSize());
    // resize in the inner vectors and fill every position with a Stone Object. (have to do all this because I dont have a default constructor)
    for (int row = 0; row < m_currentBoard.getCurrentBoardSize(); row++) 
    {
        m_stonePositions2d[row].resize(m_currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1));
    }
    /////
   // sf::Vector2i horPos(1,1);
   // m_passButton(m_textures, horPos);

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
    Game::handleGameLogic(window,GameState);


}

void Game::drawText()
{

}

void Game::createStone(Stone::COLOR side, int x, int y)
{
    int Xindex = x / (m_currentBoard.getBoardPixelSize().x / m_currentBoard.getCurrentBoardSize());
    int Yindex = y / (m_currentBoard.getBoardPixelSize().x / m_currentBoard.getCurrentBoardSize());
    
    //Sort away clicks that are outside of the board.
    if (Xindex > m_currentBoard.getCurrentBoardSize()-1 || Yindex > m_currentBoard.getCurrentBoardSize()-1)
        return;

    std::cout << "Xindex: " << Xindex << std::endl;
    std::cout << "Yindex " << Yindex << std::endl;

    m_stonePositions2d[Xindex][Yindex].setSide(side);
    m_stonePositions2d[Xindex][Yindex].setSprite(side);
    m_stonePositions2d[Xindex][Yindex].setPosition(x, y);

    }

void Game::updateTextScore(GameLogic& GameState)
{
    auto blackScoreStr = std::to_string(GameState.getBlackScore());
    m_textVector[0].setText("BLACK: " + blackScoreStr);
    auto whiteScoreStr = std::to_string(GameState.getWhiteScore());
    m_textVector[1].setText("WHITE: " + whiteScoreStr);



}

void Game::handleGameLogic(sf::RenderWindow& window, GameLogic& GameState)
{
    //Create gameLogic
    //Get the corresponding Board Index of the click.
    sf::Vector2i clickedBoardPositionIndex(GameState.findClickedBoardPositionIndex(m_worldMousePos, m_currentBoard, m_stonePositions2d[0][0].getStonePixelSize()));

    //Return if clicked outside of the Board, //Later we will have buttons like Resign etc so then this would have to change.
    if (clickedBoardPositionIndex.x == -1)
    {
        return; //Clicked outside of the board.
    }

    bool isSquareEmpty = GameState.checkIfSquareEmpty(m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]);

    bool possibleSuicideMove = false;
    bool possibleIllegalKoMove = false;
    //Put into a method func addMoveToVector().
    if (isSquareEmpty)
    {
        //Check if move results in suicide
        //call removeDeadStones for the side that just made a move.if his own stones died then its an illegal move.
        // return the killed stones.
        if (GameState.checkForSuicideMove(GameState.getCurrentSide(), m_currentBoard.getCurrentBoardSize(), m_stonePositions2d, clickedBoardPositionIndex))
            possibleSuicideMove = true;
        // Check if move is KO
        if (GameState.checkKoCoordsSameAsCurrentMove(clickedBoardPositionIndex))// Have to take into account which side makes the move
            possibleIllegalKoMove = true;

        //Make the move. (maybe put into func)
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(GameState.getCurrentSide());
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSprite(GameState.getCurrentSide());
        sf::Vector2u stoneTextureSize(m_stonePositions2d[0][0].getStonePixelSize());
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]
            .setPosition(stoneTextureSize.x * clickedBoardPositionIndex.x, stoneTextureSize.y * clickedBoardPositionIndex.y);
    }


    int nrOfDeadStones = 0;
    //Check if the move just made caused any dead stones for the opponent.
    if (GameState.getCurrentSide() == Stone::COLOR::BLACK) // Black made a move, remove dead stones for white
    {
        // If no stones where killed AND the move was a possible suicide move then revert the move and simply return because
        // It is an illegal move.
        nrOfDeadStones = GameState.removeDeadStones(Stone::COLOR::WHITE, m_currentBoard.getCurrentBoardSize(), m_stonePositions2d, 0);
        if (!nrOfDeadStones && possibleSuicideMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE); //revert move
            return;
        }
        else if (nrOfDeadStones > 1)
            GameState.resetKoCoords();
        // if ONE single stone died by the move and the position was flagged as a KO move then it truley was a KO so revert and return
        else if (nrOfDeadStones == 1 && possibleIllegalKoMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE); //revert move
            return;
        }

    }
    else // White made a move, remove dead stones for Black.
    {
        nrOfDeadStones = GameState.removeDeadStones(Stone::COLOR::BLACK, m_currentBoard.getCurrentBoardSize(), m_stonePositions2d, 0);
        if (!nrOfDeadStones && possibleSuicideMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE);
            return;
        }
        else if (nrOfDeadStones > 1) // If over one stone died then it was NOT a Ko move
            GameState.resetKoCoords();
        // if ONE single stone died by the move and the position was flagged as a KO move then it truley was a KO so revert and return
        else if (nrOfDeadStones == 1 && possibleIllegalKoMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE); //revert move
            return;
        }

    }
    GameState.updateScore(nrOfDeadStones, GameState.getCurrentSide());


    //Reset Current Ko Coords
    GameState.resetKoCoords();

    //call GameState function that checks if the last move caused a Ko situation.
    if (GameState.isKo(GameState.getCurrentSide(), m_currentBoard.getCurrentBoardSize(), m_stonePositions2d))
    {
        GameState.setKoCoords();
    }


    //Update score Text
    updateTextScore(GameState);
    GameState.changeSide();
}


void Game::drawBoard(sf::RenderWindow& window)
{
    // 0 means 9x9 board, change later so the player can specify board size from menu buttons
    window.draw(m_currentBoard.getBoard()); //Måste få in Board här på något sätt. Maybe Game has a parameter that takes in boardsize when it is created.
    // Gets board size from a menu click or something.
}

void Game::drawStones(sf::RenderWindow& window)
{
     //Loop through all the stones in the m_stonePositions2d vector and draw them.
    for (int row = 0; row < m_currentBoard.getCurrentBoardSize(); row++)
    {
        // another for loop going thorugh the y axis
        for (int col = 0; col < m_currentBoard.getCurrentBoardSize(); col++)
        {


            if (m_stonePositions2d[row][col].getSide() != Stone::NO_STONE)
            {
                window.draw(m_stonePositions2d[row][col].getStoneSprite());
            }
            
        }
    }




}





