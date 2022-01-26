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
    , m_9x9Button(m_textures)
    , m_13x13Button(m_textures)
    , m_19x19Button(m_textures)
    , m_blackPassed(0)
    , m_whitePassed(0)
    , m_currentGameState(GameLogic::GameState::TitleScreen)
    , m_currentside(Stone::COLOR::BLACK)

{
}

bool Game::interact(sf::RenderWindow & window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                /* Debugging
                std::cout << "the LEFT button was pressed" << std::endl;
                std::cout << "Pixel System mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "Pixel System mouse y: " << event.mouseButton.y << std::endl;
                */
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                m_worldMousePos = window.mapPixelToCoords(mousePos);
                /* Debugging
                std::cout << "Coords System mouse x: " << std::round(m_worldMousePos.x) << std::endl;
                std::cout << "Coords System mouse y: " << std::round(m_worldMousePos.y) << std::endl;
                */
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

    if (m_currentGameState == GameLogic::GameState::TitleScreen)
    {
        window.draw(m_9x9Button.getSprite());
        window.draw(m_13x13Button.getSprite());
        window.draw(m_19x19Button.getSprite());
    }

    if (m_currentGameState == GameLogic::GameState::GamePlay)
    {
        drawBoard(window);
        drawStones(window);
        window.draw(m_passButton.getSprite());

        // Put into function.
        sf::Vertex line[2];
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        if (m_currentside == Stone::COLOR::BLACK)
        {
            line[0].position = sf::Vector2f(m_textVector[BLACK].getPosition().x, m_textVector[BLACK].getPosition().y + 12);
            line[1].position = sf::Vector2f(m_textVector[BLACK].getPosition().x + 50 , m_textVector[BLACK].getPosition().y + 12);
        }
        else
        {
            line[0].position = sf::Vector2f(m_textVector[WHITE].getPosition().x, m_textVector[WHITE].getPosition().y + 12);
            line[1].position = sf::Vector2f(m_textVector[WHITE].getPosition().x + 50, m_textVector[WHITE].getPosition().y + 12);
        }
        window.draw(line, 2, sf::Lines);

        
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
        window.draw(m_textVector[2].getText());
    }

    if (m_currentGameState == GameLogic::GameState::PresentWinner)
    {
        drawBoard(window);
        drawStones(window);
        drawStonesScoring(window);
        window.draw(m_doneButton.getSprite());
        Game::drawText(window);
        window.draw(m_textVector[3].getText()); //Winner text (maybe change to enum)
        window.draw(m_textVector[4].getText()); //Play again text (maybe change to enum)
        window.draw(m_yesButton.getSprite());
        window.draw(m_noButton.getSprite());
    }
}

void Game::update(sf::RenderWindow& window, GameLogic& GameState)
{
    if (m_currentGameState == GameLogic::GameState::TitleScreen)
    {
        static int first = 1;

        if (first)
        {
            // initilize the Board size buttons. (we need to do this first before we initialise Stone vector and text etc.
            initBaseSpriteObject(m_9x9Button, "Sprites/9x9.png", TextureHolder::ID::NINE, 2, sf::Vector2i(100, 100));
            initBaseSpriteObject(m_13x13Button, "Sprites/13x13.png", TextureHolder::ID::THIRTEEN, 2, sf::Vector2i(200, 100));
            initBaseSpriteObject(m_19x19Button, "Sprites/19x19.png", TextureHolder::ID::NINETEEN, 2, sf::Vector2i(320, 100));
            first = 0;
            return;
        }
        if (handleBoardSizeButtonFunctionality())
        {
            // --Initilize Game--
            // Set stone vector length
            Game::initStoneVectors(); // Have to do it here since it depends on the board size
            // Initilize and set text and button positions. (depends on board size)
            Game::initText();
            initBaseSpriteObject(m_passIcon, "Sprites/passIcon.png", TextureHolder::ID::PassIcon, 0.05, sf::Vector2i(m_textVector[BLACK].getText().getPosition().x, m_textVector[BLACK].getText().getPosition().y + 10));
            initBaseSpriteObject(m_passButton, "Sprites/passbutton.png", TextureHolder::ID::Pass, 0.1, sf::Vector2i(m_textVector[SCORING_PHASE].getText().getPosition().x + 20, m_textVector[SCORING_PHASE].getText().getPosition().y + 5));
            initBaseSpriteObject(m_doneButton, "Sprites/doneButton.png", TextureHolder::ID::Done, 0.1, sf::Vector2i(m_textVector[SCORING_PHASE].getText().getPosition().x + 20, m_textVector[SCORING_PHASE].getText().getPosition().y + 5));
            initBaseSpriteObject(m_yesButton, "Sprites/yesButton.png", TextureHolder::ID::Yes, 0.1, sf::Vector2i(m_textVector[PLAY_AGAIN].getText().getPosition().x - 10, m_textVector[PLAY_AGAIN].getText().getPosition().y));
            initBaseSpriteObject(m_noButton, "Sprites/noButton.png", TextureHolder::ID::No, 0.1, sf::Vector2i(m_textVector[PLAY_AGAIN].getText().getPosition().x + 40, m_textVector[PLAY_AGAIN].getText().getPosition().y));
        }
        return;
    }

    if (m_currentGameState == GameLogic::GameState::GamePlay)
    {
        Game::handlePassFunctionality(GameState);
        Game::handleMakingMoveLogic(window, GameState);
        GameState.setWinner(); // Set current winner if the game would finish without counting territory
        m_currentside = GameState.getCurrentSide();
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
        GameState.resetVisitedArray((int)m_currentBoard.getCurrentBoardSize());
        GameState.floodFillArea(targetSide, replacementColor, m_stonePositions2d, m_scoreStonePositions2d, clickedBoardPositionIndex.x, clickedBoardPositionIndex.y);
        // Update total score with the territory score!
        // loop through the scoring vector and count all points and add it to the respective sides score stored in GameLogic.cpp

        int blacksTerritoryScore = 0;
        int whitesTerritoryScore = 0;
        for (int x = 0; x < (int)m_currentBoard.getCurrentBoardSize(); x++) for (int y = 0; y < (int) m_currentBoard.getCurrentBoardSize(); y++)
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
    }

    if (m_currentGameState == GameLogic::GameState::PresentWinner)
    {
        // Handle "play again" button functionality and when that button is pressed reset score and vectors!
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
            for (int x = 0; x <(int) m_currentBoard.getCurrentBoardSize(); x++) for (int y = 0; y <(int) m_currentBoard.getCurrentBoardSize(); y++)
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
    for (int i = 0; i < 2; i++)
        window.draw(m_textVector[i].getText());
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
        m_textVector[WINNER].setText("BLACK WINNS!");
    }
    else if (GameState.getWinner() == Stone::COLOR::WHITE)
    {
        m_textVector[WINNER].setText("WHITE WINNS!");
    }
    else
        m_textVector[WINNER].setText("DRAW!");
}

void Game::initStoneVectors()
{
    //Put this in a function (init Stones)
    sf::Image tempImage;
    tempImage.loadFromFile("Sprites/white_black.png");
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(TextureHolder::ID::Stone, tempImage);
      
    // resize the outer vector
    m_stonePositions2d.resize((int)m_currentBoard.getCurrentBoardSize());
    m_scoreStonePositions2d.resize((int)m_currentBoard.getCurrentBoardSize());
    // resize in the inner vectors and fill every position with a Stone Object. (have to do all this because I dont have a default constructor)
    for (int row = 0; row < (int)m_currentBoard.getCurrentBoardSize(); row++)
    {
        m_stonePositions2d[row].resize((int)m_currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1, 1));
        m_scoreStonePositions2d[row].resize((int)m_currentBoard.getCurrentBoardSize(), Stone(m_textures, Stone::COLOR::NO_STONE, 1, 1, 1));
    }
}

void Game::initBaseSpriteObject(BaseSprite & sprite,const std::string& filename, TextureHolder::ID id, float scale, sf::Vector2i pos)
{
    sf::Image tempImage;
    // Load Pass indicator sprite.
    tempImage.loadFromFile(filename);
    tempImage.createMaskFromColor(sf::Color::White);
    m_textures.load(id, tempImage);
    sprite.loadSprite(id);
    sprite.setScale(scale, scale);
    sprite.setPosition(pos);
}

void Game::initText()
{
    //Load text font
    m_fonts.load(FontHolder::FontID::PixelFont, "Fonts/slkscre.ttf");
    //Create and put text in array  

    TextStrings blackText(m_fonts, "BLACK: 0", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(m_currentBoard.getBoardPixelSize().x + 5, 0)); //boardTextureSize.x/10, boardTextureSize.y*1.05));
    m_textVector.emplace_back(blackText); // 0

    TextStrings whiteText(m_fonts, "WHITE: 0", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(m_textVector[BLACK].getText().getPosition().x + 80, m_textVector[BLACK].getText().getPosition().y)); //sf::Vector2u(boardTextureSize.x * 6 / 10, boardTextureSize.y * 1.05));
    m_textVector.emplace_back(whiteText); // 1

    TextStrings scoringPhase(m_fonts, "Scoring Phase", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(m_textVector[BLACK].getText().getPosition().x + 25, m_textVector[BLACK].getText().getPosition().y + 10));
    m_textVector.emplace_back(scoringPhase); // 2

    TextStrings winnerDeclerationText(m_fonts, "", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(m_textVector[BLACK].getText().getPosition().x + 30, m_textVector[BLACK].getText().getPosition().y + 50));// boardTextureSize.y * 1.4));
    m_textVector.emplace_back(winnerDeclerationText); // 3

    TextStrings playAgainText(m_fonts, "PLAY AGAIN?", sf::Color::White, 10, sf::Text::Bold, sf::Vector2u(m_textVector[WINNER].getText().getPosition().x, m_textVector[WINNER].getText().getPosition().y + 10));//boardTextureSize.y * 1.5));
    m_textVector.emplace_back(playAgainText); // 4

}

bool Game::handleBoardSizeButtonFunctionality()
{
    // If returns true then the user has selected a board and we can continue to initilise everything with the right size.
    sf::FloatRect v9x9ButtonBounds = m_9x9Button.getSprite().getGlobalBounds();
    sf::FloatRect v13x13ButtonBounds = m_13x13Button.getSprite().getGlobalBounds();
    sf::FloatRect v19x19ButtonBounds = m_19x19Button.getSprite().getGlobalBounds();

    if (v9x9ButtonBounds.contains(m_worldMousePos))
    {
        m_currentBoard.selectBoardSize(BOARDSIZE::BOARD_9x9);
        m_currentGameState = GameLogic::GameState::GamePlay;
        return true;
    }
    else if (v13x13ButtonBounds.contains(m_worldMousePos))
    {
        m_currentBoard.selectBoardSize(BOARDSIZE::BOARD_13x13);
        m_currentGameState = GameLogic::GameState::GamePlay;
        return true;
    }
    else if (v19x19ButtonBounds.contains(m_worldMousePos))
    {
        m_currentBoard.selectBoardSize(BOARDSIZE::BOARD_19x19);
        m_currentGameState = GameLogic::GameState::GamePlay;
        return true;
    }
    else
        return false;         //Do nothing, clicked outside of the buttons.

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
    bool possibleSuicideMove = false; //reset these before we start
    bool possibleIllegalKoMove = false; //reset these before we start
    //Put into a method func addMoveToVector().
    if (isSquareEmpty)
    {
        //Check if move results in suicide
        //call removeDeadStones for the side that just made a move.if his own stones died then its an illegal move.
        // return the killed stones.
        if (GameState.checkForSuicideMove(GameState.getCurrentSide(), (int)m_currentBoard.getCurrentBoardSize(), m_stonePositions2d, clickedBoardPositionIndex))
            possibleSuicideMove = true;
        // Check if move is KO
        if (GameState.checkKoCoordsSameAsCurrentMove(clickedBoardPositionIndex))// Have to take into account which side makes the move
            possibleIllegalKoMove = true; //Not sure yet if its KO or not because if more than 1 stones dies it is NOT KO

        //Make the move. (can be reversed if it was a KO move) (maybe put into func)
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(GameState.getCurrentSide());
        m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSprite(GameState.getCurrentSide());
        sf::Vector2u stoneTextureSize(m_stonePositions2d[0][0].getStonePixelSize());
        // quick hack to just move the origin of the stons to the center of the stone instead of the top left corner (makes scaling easier later)
        // Edit; this "hack" should be done elsewhere, not in the logic...
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

    int nrOfDeadStones = 0; //reset this before we start
    //Check if the move just made caused any dead stones for the opponent.
    if (GameState.getCurrentSide() == Stone::COLOR::BLACK) // Black made a move, remove dead stones for white
    {
        // If no stones where killed AND the move was a possible suicide move then revert the move and simply return because...
        // ... It is an illegal move.
        nrOfDeadStones = GameState.removeDeadStones(Stone::COLOR::WHITE, static_cast<int>(m_currentBoard.getCurrentBoardSize()), m_stonePositions2d, 0);
        if (!nrOfDeadStones && possibleSuicideMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE); //revert move because its a suicide move
            return;
        }
        else if (nrOfDeadStones > 1) //cant be KO if more than 1 stone died.
            GameState.resetKoCoords();
        // if ONE single stone died by the move and the position was flagged as a KO move then it truley was a KO so revert and return
        else if (nrOfDeadStones == 1 && possibleIllegalKoMove)
        {
            m_stonePositions2d[clickedBoardPositionIndex.x][clickedBoardPositionIndex.y].setSide(Stone::COLOR::NO_STONE); //revert move just made
             // Also revert the stone that died.
            // Revert the single captured stone.
            GameState.revertCapturedStone(m_stonePositions2d, Stone::COLOR::WHITE);
            return;
        }
    }
    else // White made a move, remove dead stones for Black.
    {
        nrOfDeadStones = GameState.removeDeadStones(Stone::COLOR::BLACK, (int)m_currentBoard.getCurrentBoardSize(), m_stonePositions2d, 0);
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
            GameState.revertCapturedStone(m_stonePositions2d, Stone::COLOR::BLACK);
            return;
        }
    }
    GameState.updateScore(nrOfDeadStones, GameState.getCurrentSide());

    //Reset Current Ko Coords
    GameState.resetKoCoords();

    //call GameState function that checks if the last move caused a Ko situation.
    if (GameState.isKo(GameState.getCurrentSide(), (int)m_currentBoard.getCurrentBoardSize(), m_stonePositions2d))
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
    for (int row = 0; row < (int)m_currentBoard.getCurrentBoardSize(); row++)
    {
        // another for loop going thorugh the y axis
        for (int col = 0; col < (int) m_currentBoard.getCurrentBoardSize(); col++)
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
    for (int row = 0; row <(int) m_currentBoard.getCurrentBoardSize(); row++)
    {
        // another for loop going thorugh the y axis
        for (int col = 0; col <(int) m_currentBoard.getCurrentBoardSize(); col++)
        {
            if (m_scoreStonePositions2d[row][col].getSide() != Stone::COLOR::NO_STONE)
            {
                m_scoreStonePositions2d[row][col].setScale(0.5, 0.5);
                window.draw(m_scoreStonePositions2d[row][col].getStoneSprite());
            }
        }
    }
}
