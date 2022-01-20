#include "Game.h"
#include <iostream> // Needed for std::cout
#include <cmath>
#include <string>


Game::Game()
    : m_passButton(m_textures)
    , m_passIcon(m_textures)
    , m_doneButton(m_textures)
    , m_yesButton(m_textures)
    , m_noButton(m_textures)
    , m_blackPassed(0)
    , m_whitePassed(0)
    , m_currentGameState(GameLogic::GameState::GamePlay)
    , m_smallStone(m_textures)
{

    //Load text font
    m_fonts.load(FontHolder::FontID::Ariel, "Fonts/slkscre.ttf");
    //Create and put text in array  
    sf::Vector2u boardTextureSize(m_currentBoard.getBoardPixelSize());
    TextStrings blackText(m_fonts,"BLACK: 0",sf::Color::White,10,sf::Text::Bold,sf::Vector2u(boardTextureSize.x/10, boardTextureSize.y*1.05));
    m_textVector.emplace_back(blackText);

    TextStrings whiteText(m_fonts, "WHITE: 0", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(boardTextureSize.x * 6 / 10, boardTextureSize.y * 1.05));
    m_textVector.emplace_back(whiteText);

    TextStrings winnerDeclerationText(m_fonts, "", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(boardTextureSize.x / 4, boardTextureSize.y * 1.4));
    m_textVector.emplace_back(winnerDeclerationText);

    TextStrings playAgainText(m_fonts, "PLAY AGAIN?", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(boardTextureSize.x / 4, boardTextureSize.y * 1.5));
    m_textVector.emplace_back(playAgainText);

    //Put this in a function (init Stones)
    sf::Image tempImage;
    tempImage.loadFromFile("Sprites/white_black.png");
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::Stone, tempImage);

    //Load Stone texture
    //m_textures.load(TextureHolder::ID::Stone, "Sprites/white_black.png");
    // resize the outer vector
    m_stonePositions2d.resize(m_currentBoard.getCurrentBoardSize());
    m_scoreStonePositions2d.resize(m_currentBoard.getCurrentBoardSize());
    // resize in the inner vectors and fill every position with a Stone Object. (have to do all this because I dont have a default constructor)
    for (int row = 0; row < m_currentBoard.getCurrentBoardSize(); row++) 
    {
        m_stonePositions2d[row].resize(m_currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1));
        m_scoreStonePositions2d[row].resize(m_currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1));

    }

    //Load  pass button sprite (put into function)
    //sf::Image tempImage;
    tempImage.loadFromFile("Sprites/passbutton.png");
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::Pass, tempImage);
    m_passButton.loadSprite(TextureHolder::ID::Pass);
    m_passButton.setScale(0.1, 0.1);
    m_passButton.setPosition(sf::Vector2i(60, 200));

    // Load Pass indicator sprite.
    tempImage.loadFromFile("Sprites/passIcon.png");
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::PassIcon, tempImage);
    m_passIcon.loadSprite(TextureHolder::ID::PassIcon);
    m_passIcon.setScale(0.05, 0.05);
    m_passIcon.setPosition(sf::Vector2i(m_textVector[0].getText().getPosition().x, m_textVector[0].getText().getPosition().y + 10)); // 100, 190

    // Load Done Button sprite
    tempImage.loadFromFile("Sprites/doneButton.png"); // Temporary, change to DONE button
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::Done, tempImage);
    m_doneButton.loadSprite(TextureHolder::ID::Done);
    m_doneButton.setScale(0.1, 0.1);
    m_doneButton.setPosition(sf::Vector2i(60, 200)); 

    // Load yes button sprite
    tempImage.loadFromFile("Sprites/yesButton.png"); // Temporary, change to DONE button
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::Yes, tempImage);
    m_yesButton.loadSprite(TextureHolder::ID::Yes);
    m_yesButton.setScale(0.1, 0.1);
    m_yesButton.setPosition(sf::Vector2i(boardTextureSize.x / 5, boardTextureSize.y * 1.5));

    // Load no button sprite
    tempImage.loadFromFile("Sprites/noButton.png"); // Temporary, change to DONE button
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::No, tempImage);
    m_noButton.loadSprite(TextureHolder::ID::No);
    m_noButton.setScale(0.1, 0.1);
    m_noButton.setPosition(sf::Vector2i(boardTextureSize.x / 2, boardTextureSize.y * 1.5));


    //tempImage.loadFromFile("Sprites/black.png");
    //tempImage.createMaskFromColor(sf::Color::White);
    //m_textures.load(TextureHolder::ID::StoneBlack, tempImage);
    //m_smallStone.loadSprite(TextureHolder::ID::StoneBlack);

    //m_smallStone.setPosition(sf::Vector2i(9, 9));
    //m_smallStone.setOrigin(9.5, 9.5);
    //m_smallStone.setScale(0.5, 0.5);

}

//Command * Game::interact(sf::RenderWindow & window)
bool Game::interact(sf::RenderWindow & window)
{
    sf::Event event;
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
            return true;
        }
        else
            return false;

    }
    return false;
}

void Game::drawGame(sf::RenderWindow& window)
{
    if (m_currentGameState == GameLogic::GameState::GamePlay)
    {
        drawBoard(window);
        drawStones(window);
        window.draw(m_passButton.getSprite());

        // put into function
        if (m_blackPassed)
        {
            sf::Vector2i pos(m_textVector[0].getText().getPosition().x, m_textVector[0].getText().getPosition().y + 10);
            m_passIcon.setPosition(pos);
            window.draw(m_passIcon.getSprite());
        }
        if (m_whitePassed)
        {
            sf::Vector2i pos(m_textVector[1].getText().getPosition().x, m_textVector[1].getText().getPosition().y + 10);
            m_passIcon.setPosition(pos);
            window.draw(m_passIcon.getSprite());
        }
        Game::drawText(window);
    }


   

    if (m_currentGameState == GameLogic::GameState::ScoreCounting)
    {
        drawBoard(window);
        drawStones(window);
        drawStonesScoring(window);
        window.draw(m_doneButton.getSprite());
        Game::drawText(window);


    }

    if (m_currentGameState == GameLogic::GameState::PresentWinner)
    {
        drawBoard(window);
        drawStones(window);
        drawStonesScoring(window);
        window.draw(m_doneButton.getSprite());
        Game::drawText(window);
        window.draw(m_textVector[2].getText()); //Winner text (maybe change to enum)
        window.draw(m_textVector[3].getText()); //Play again text (maybe change to enum)
        window.draw(m_yesButton.getSprite());
        window.draw(m_noButton.getSprite());
        

    }

}

void Game::makeMove(Stone::COLOR side)
{   
    createStone(Stone::COLOR::WHITE, 40, 40);

}

void Game::update(sf::RenderWindow& window, GameLogic& GameState)
{

    // Have another GameState here called GameSetup where we set the Boardsize. 
    // #DONE Step 0  create the two other game boards in paint.
    // Step 1 change the board class so it doesn't have a constructor,
     // Step 2 create a set function for the board class where we set the board size
    // create some buttons we can click on 9, 13, 19 and clicking one of those buttons will call the set function and set the correct board size.
    // Step 3 make sure the board size member variable gets the correct size.
    //  Step 4 Hopefully game functionality will scale with the size BUT the Button and text position needs to be adjusted
    // kommentar, I andra GO spel n'r man valjer bigger or osmaller screen, the stones become bigger and smaller but the screen size remains the same.
    if (m_currentGameState == GameLogic::GameState::GamePlay)
    {
        Game::handlePassFunctionality(GameState);
        Game::handleMakingMoveLogic(window, GameState);
        GameState.setWinner(); // Set current winner if the game would finish without counting territory
        return;
    }

    if (m_currentGameState == GameLogic::GameState::ScoreCounting)
    {
        // put into function, handle Pressing DONE button functionality
        sf::FloatRect doneButtonBounds = m_doneButton.getSprite().getGlobalBounds();

        if (doneButtonBounds.contains(m_worldMousePos))
        {
            //Go to final Winner presenter screen!
            m_currentGameState = GameLogic::GameState::PresentWinner;
            updateWinnerText(GameState);
        }

        // put into function, handle score counting functionality
        sf::Vector2i clickedBoardPositionIndex(GameState.findClickedBoardPositionIndex(m_worldMousePos, m_currentBoard, m_stonePositions2d[0][0].getStonePixelSize()));

        //Return if clicked outside of the Board, //Later we will have buttons like Resign etc so then this would have to change.
        if (clickedBoardPositionIndex.x == -1)
        {
            return; //Clicked outside of the board.
        }
        Stone::COLOR targetSide = m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].getSide();
        Stone::COLOR replacementColor;
        static int cycle = 0; // cycle through NO_STONE ->BLACK -> WHITE -> NO_STONE
        switch(cycle)
        {
        case(0):
            replacementColor = Stone::COLOR::BLACK;
            cycle++;
            break;
        case(1):
            replacementColor = Stone::COLOR::WHITE;
            cycle++;
            break;
        case(2):
            replacementColor = Stone::COLOR::NO_STONE;
            cycle = 0;
            break;
        default:
            replacementColor = Stone::COLOR::NO_STONE;
            break;

            Game::handleDoneButtonFunctionality(GameState);
        }

        //Reset m_visited;
        GameState.resetVisitedArray(m_currentBoard.getCurrentBoardSize());
        GameState.floodFillArea(targetSide, replacementColor, m_stonePositions2d, m_scoreStonePositions2d, clickedBoardPositionIndex.x, clickedBoardPositionIndex.y);
        // Update total score with the territory score!
        // loop through the scoring vector and count all points and add it to the respective sides score stored in GameLogic.cpp

        int blacksTerritoryScore = 0;
        int whitesTerritoryScore = 0;
        for (int x = 0; x < m_currentBoard.getCurrentBoardSize(); x++) for (int y = 0; y < m_currentBoard.getCurrentBoardSize(); y++)
        {
            if (m_scoreStonePositions2d[x][y].getSide() == Stone::COLOR::BLACK)
            {
                //add score to blacks territory score
                blacksTerritoryScore++;
            }
            else if (m_scoreStonePositions2d[x][y].getSide() == Stone::COLOR::WHITE)
            {
                // add score to Whites territory Score 
                whitesTerritoryScore++;
            }
        }
        GameState.addTerritoryScore(Stone::COLOR::BLACK, blacksTerritoryScore);
        GameState.addTerritoryScore(Stone::COLOR::WHITE, whitesTerritoryScore);


        //update the scorebut with seperate variables.
        updateTextScore(GameState);
        // Set player with highest score as winner to show when we press DONE
        GameState.setWinner();
        //updateWinnerText(GameState);






        // A click will look through all connecting squares, if we press an empty square it will check all connecting empty squares,
        //  if we press black then it will check all connecting black squares etc.
        // As we find all connecting squares, Mark each connecting square with a  mini black, mini white, or empty square.
        // Already laid stones will have a small square ontop of them. So have to make a second stone vector.
        // #DONE Step 1 Make a second stone vector, should be exactly same as the other one.
        // #DONE Step 2 Modify and implement the flood fill algorithm so that it goes through all connected stones and instead of returning if a stone is 
        // dead or aline, add it to the New stone vector, if its empty -> add black stones, if its black -> add white stones, and if its white 
        //-> remove stone.
        // DONE Step 3 When the players are sadisfied, have them press the "DONE" button that replaces the pass button.
        // Step 4 when we press DONE we move to the final phase which is show final score phase. here we calculate the score by adding 
        // nr of dead stones + the number of small stones for each side in the 2nd vector! that will result in an accurate score!!
        // Declare the winner then show two buttons that says play again and quit game. Play again will reset everything and move to phase gameplay
        // quit will simply close the window :) Game done!!!

        
        /*
        bool isSquareEmpty = GameState.checkIfSquareEmpty(m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]);
        if (isSquareEmpty)
        {
            //Make the move. (maybe put into func)
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(GameState.getCurrentSide());
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSprite(GameState.getCurrentSide());
            sf::Vector2u stoneTextureSize(m_stonePositions2d[0][0].getStonePixelSize());
            // quick hack to just move the origin of the stons to the center of the stone instead of the top left corner (makes scaling easier later)
            float originOffset = 9.5;
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setOrigin(originOffset, originOffset);
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setScale(0.5,0.5);

            //
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]
                .setPosition(stoneTextureSize.x * clickedBoardPositionIndex.x + originOffset, stoneTextureSize.y * clickedBoardPositionIndex.y + originOffset);


        }
        */
        
    }

    if (m_currentGameState == GameLogic::GameState::PresentWinner)
    {
        // Handle "play again" button functionality and when that button is pressed reset score and vectors!
                // put into function, handle Pressing Yes and No button functionality
        sf::FloatRect yesButtonBounds = m_yesButton.getSprite().getGlobalBounds();
        sf::FloatRect noButtonBounds = m_noButton.getSprite().getGlobalBounds();

        if (yesButtonBounds.contains(m_worldMousePos))
        {
            // Reset everything!
            // put into a function reset function
            GameState.resetEverything();
            m_blackPassed = false;
            m_whitePassed = false;
            GameState.setSide(Stone::COLOR::BLACK);
            for (int x = 0; x < m_currentBoard.getCurrentBoardSize(); x++) for (int y = 0; y < m_currentBoard.getCurrentBoardSize(); y++)
            {
                m_scoreStonePositions2d[x][y].setSide(Stone::COLOR::NO_STONE);
                m_stonePositions2d[x][y].setSide(Stone::COLOR::NO_STONE);
                m_currentGameState = GameLogic::GameState::GamePlay;
            }
        }

        if (noButtonBounds.contains(m_worldMousePos))
        {
            // close the screen
            window.close();
        }
    }


}

void Game::drawText(sf::RenderWindow& window)
{
    //for (auto& value : m_textVector)
    //{
    //    window.draw(value.getText());
    //}
    for (int i = 0; i < 2; i++)
        window.draw(m_textVector[i].getText());
    
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

void Game::updateWinnerText(GameLogic& GameState)
{
    if (GameState.getWinner() == Stone::COLOR::BLACK)
    {
        m_textVector[2].setText("BLACK WINNS!");
    }
    else if (GameState.getWinner() == Stone::COLOR::WHITE)
    {
        m_textVector[2].setText("WHITE WINNS!");
    }
    else
        m_textVector[2].setText("DRAW!");


}

void Game::handleMakingMoveLogic(sf::RenderWindow& window, GameLogic& GameState)
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
        // quick hack to just move the origin of the stons to the center of the stone instead of the top left corner (makes scaling easier later)
        float originOffset = 9.5;
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setOrigin(originOffset, originOffset);
        //
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y]
            .setPosition(stoneTextureSize.x * clickedBoardPositionIndex.x + originOffset, stoneTextureSize.y * clickedBoardPositionIndex.y + originOffset);


    }
    else //square not empty
    {
        return;
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

    //Reset Pass flag (if the player made a valid move then reset the other players pass flag.
    if (GameState.getCurrentSide() == Stone::COLOR::BLACK)
    {
        m_whitePassed = false;
    }
    else
        m_blackPassed = false;

    //Update score Text
    updateTextScore(GameState);
    GameState.changeSide();
}

void Game::handlePassFunctionality(GameLogic& GameState)
{
    //Handle pass functionality
    sf::FloatRect passButtonBounds = m_passButton.getSprite().getGlobalBounds();

    if (passButtonBounds.contains(m_worldMousePos))
    {
        //Set players turn that clicked pass flag to true.
        // In drawGame have a if statment check if flags are true and if true then draw pass sign.
        if (GameState.getCurrentSide() == Stone::COLOR::BLACK)
        {
            m_blackPassed = true;
            GameState.changeSide();
        }
        else
        {
            m_whitePassed = true;
            GameState.changeSide();
        }
    }
    if (m_blackPassed && m_whitePassed)
    {
        //Game over, Go to score mode.
        m_currentGameState = GameLogic::GameState::ScoreCounting;
    }
}

void Game::handleDoneButtonFunctionality(GameLogic& GameState)
{
    //Handle Done button functionality
    sf::FloatRect doneButtonBounds = m_doneButton.getSprite().getGlobalBounds();

    if (doneButtonBounds.contains(m_worldMousePos))
    {
        m_currentGameState = GameLogic::GameState::PresentWinner;
    }
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


            if (m_stonePositions2d[row][col].getSide() != Stone::COLOR::NO_STONE)
            {
                window.draw(m_stonePositions2d[row][col].getStoneSprite());
            }
        }
    }




}

void Game::drawStonesScoring(sf::RenderWindow& window)
{
     // Also draw the smaller stones that represent captured area
         //Loop through all the stones in the m_stonePositions2d vector and draw them.
    for (int row = 0; row < m_currentBoard.getCurrentBoardSize(); row++)
    {
        // another for loop going thorugh the y axis
        for (int col = 0; col < m_currentBoard.getCurrentBoardSize(); col++)
        {


            if (m_scoreStonePositions2d[row][col].getSide() != Stone::COLOR::NO_STONE)
            {
                m_scoreStonePositions2d[row][col].setScale(0.5, 0.5);
                window.draw(m_scoreStonePositions2d[row][col].getStoneSprite());
            }
        }
    }
}





