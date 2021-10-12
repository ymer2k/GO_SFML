#include <SFML/Graphics.hpp>
#include <iostream> // Needed for sf::Keyboard
#include <vector>

#include "Render.h"
#include "Game.h"

//Prototypes
void runGame();
bool isInsideArea(int x1, int y1, int x2,
    int y2, int x, int y);

void oldMain()
{
    const int BORDER_X = 0;
    const int BORDER_Y = 0;
    const int BOARD_SIZE = 9;

    sf::Vector2i StoneLocations[BOARD_SIZE][BOARD_SIZE]; // stores the pices locations.
    sf::Vector3i THStoneLocations[BOARD_SIZE][BOARD_SIZE]; // stores the pices locations. Have to use 3i because i want to save 3d coords into this vector. x, y and side :)
    int side = 1; // white 1  black 2.

    sf::RenderWindow window(sf::VideoMode(800, 600), "Go");
    int aspectRatio = 800 / 600;
    int borderIncrease = 5;
    sf::View view = window.getView();
    view.setCenter(sf::Vector2f(200, 150));
    view.setSize(sf::Vector2f(400 + borderIncrease * aspectRatio, 300 + borderIncrease));


    sf::RectangleShape player(sf::Vector2f(160, 270));
    sf::RectangleShape board(sf::Vector2f(171, 171)); // Board texture size
    sf::RectangleShape black(sf::Vector2f(19, 19)); // stone texture size.
    sf::RectangleShape white(sf::Vector2f(19, 19));


    sf::Texture pieceTexture;
    pieceTexture.loadFromFile("Sprites/white_black.png");

    black.setTexture(&pieceTexture); //here we set the texture eventhough its the whole texture
    white.setTexture(&pieceTexture); //here we set the texture eventhough its the whole texture



    sf::Vector2u pieceTextureSize = pieceTexture.getSize();
    //here we split the texture into pieces.
    pieceTextureSize.x /= 2;
    pieceTextureSize.y /= 1; //because only one row :)

    //Get a sub texture from the collected texture Black_white.png
    black.setTextureRect(sf::IntRect(pieceTextureSize.x, 0, pieceTextureSize.x, pieceTextureSize.y)); //First two parameters are the starting positions in the texture and the other two parameters are the size of the texture
    white.setTextureRect(sf::IntRect(0, 0, pieceTextureSize.x, pieceTextureSize.y));



    player.setPosition(356, 206);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Sprites/toadP.png");
    player.setTexture(&playerTexture);

    board.setPosition(BORDER_X, BORDER_Y);
    sf::Texture boardTexture;
    boardTexture.loadFromFile("Sprites/9x9_board.png");
    std::cout << "BOARD SIZE X: " << boardTexture.getSize().x << std::endl;
    std::cout << "BOARD SIZE Y: " << boardTexture.getSize().y << std::endl;

    board.setTexture(&boardTexture);

    board.setScale(1, 1);
    black.setScale(1, 1);
    white.setScale(1, 1);

    bool released = false;


    while (window.isOpen())
    {



        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased)
            {
                released = true;
            }
        }



        //Mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (released) // To avoid constant spamming of button presses
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // window because pos realtive to the window.
                sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos); // Used to match the world coord with the current view coord.
                std::cout << "mouseWorldPos: " << worldMousePos.x << "mouseWorldPos: " << worldMousePos.y << std::endl;
                for (int row = 0; row < BOARD_SIZE; row++)
                {
                    for (int col = 0; col < BOARD_SIZE; col++)
                    {
                        //sf::Vector2i piecePos;
                        //piecePos.x = col * pieceTextureSize.x;
                        //piecePos.y = row * pieceTextureSize.y;
                        //int x2 = piecePos.x + pieceTextureSize.x;
                        //int y2 = piecePos.y + pieceTextureSize.y;

                        // TODO put in a function and move to graphics
                        sf::Vector3i piecePos;
                        piecePos.x = col * pieceTextureSize.x;
                        piecePos.y = row * pieceTextureSize.y;
                        piecePos.z = side; // also saves what stone color it is.
                        int x2 = piecePos.x + pieceTextureSize.x;
                        int y2 = piecePos.y + pieceTextureSize.y;


                        if (isInsideArea(piecePos.x, piecePos.y, x2, y2, worldMousePos.x, worldMousePos.y))
                        {
                            // TODO Move to a function in gameLogic that calls this vector?
                            if (THStoneLocations[col][row].z != 0) //If not empty
                            {
                                //blank
                            }
                            else
                            {
                                THStoneLocations[col][row] = piecePos;
                                side == 2 ? side = 1 : side = 2;  // change sides.
                            }
                            //StoneLocations[col][row] = piecePos; // stores the pices locations.


                        }
                    }
                }
                released = false;
            }
        }



        //Mouse Just to check that removing stones work. only the code in the if statment below is needed.
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (released) // To avoid constant spamming of button presses
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // window because pos realtive to the window.
                sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos); // Used to match the world coord with the current view coord.
                std::cout << "mouseWorldPos: " << worldMousePos.x << "mouseWorldPos: " << worldMousePos.y << std::endl;
                for (int row = 0; row < BOARD_SIZE; row++)
                {
                    for (int col = 0; col < BOARD_SIZE; col++)
                    {


                        sf::Vector3i piecePos;
                        piecePos.x = col * pieceTextureSize.x;
                        piecePos.y = row * pieceTextureSize.y;
                        piecePos.z = side; // also saves what stone color it is.
                        int x2 = piecePos.x + pieceTextureSize.x;
                        int y2 = piecePos.y + pieceTextureSize.y;


                        if (isInsideArea(piecePos.x, piecePos.y, x2, y2, worldMousePos.x, worldMousePos.y))
                        {
                            // TODO check if piece is already there. //maybe belongs in gamelogic
                            if (THStoneLocations[col][row].z != 0) //If not empty
                            {
                                //Remove stone 
                                //TODO put in gamelogic for when one or more stones are removed.
                                THStoneLocations[col][row].x = 0;
                                THStoneLocations[col][row].y = 0;
                                THStoneLocations[col][row].z = 0;
                                break; // make this a function and return here instead.
                            }
                        }
                    }
                }
                released = false;
            }
        }





        // drawing code.
        window.clear();
        window.draw(board);

        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                //black.setPosition(StoneLocations[i][j].x, StoneLocations[i][j].y);
                //window.draw(black);

                if (THStoneLocations[row][col].z == 1) // if white stone
                {
                    white.setPosition(THStoneLocations[row][col].x, THStoneLocations[row][col].y);
                    window.draw(white);
                }

                if (THStoneLocations[row][col].z == 2) // if black stone
                {
                    black.setPosition(THStoneLocations[row][col].x, THStoneLocations[row][col].y);
                    window.draw(black);

                }




                //white.setPosition(THStoneLocations[i][j][0].x, THStoneLocations[i][j][0].y);
                //window.draw(white);

                // black.setPosition(THStoneLocations[i][j][1].x, THStoneLocations[i][j][1].y);
                // window.draw(black);




            }

        }

        window.setView(view);
        window.draw(player);

        window.display();



    }
}

void runGame()
{
    /*
    * Game is a game object instance of the game.
        Game.resetBoard();

    
        while(!Game.isGameWon())
        {
            move = Game.getValidMove() //Current player makes a move and we check if its a valid move and returns the move if it is valid. Should return the row and col and side for the move
            updateBoard(move) // uppdate the board with the current move, not sure how this will be done. Maybe when we clikc a square we save the move if its legal and then continue to the
            print part of graphics? Dont know since the game is a continues loop that updates the "game world"
            checkDeadStones()
                Update board again if dead stones
            CheckMoreLegalMovesPossible? Or just ignore and have the player pass if no more legal moves possible, Maybe this is easier
            
            if(isScoringPhase()
                ScoringPhase();

 

        }

    
    
    
    
    */
    //

}


bool isInsideArea(int x1, int y1, int x2,
    int y2, int x, int y)
{
    //x1 and y1 is top left corner of a rectangle and x2 y2 is the bottom right. x,y is the point.
    if (x > x1 and x < x2 and y > y1 and y < y2)
        return true;

    return false;
}


int main()
{    
    //oldMain();







    //return 0;
    Render world;
    Game currentgame;

    // open main menu which is also the world.window but this time we will draw a menu instead. then when we click maybe size of the board etc it will close and we will open up the 
    // "game window".
    while (world.window.isOpen()) // the main game loop
    {
        currentgame.interact(world.window); // handles interactions with the game.
        //currentgame.makeMove(Stone::BLACK);
        world.window.clear();
        currentgame.makeMove(Stone::BLACK);
        currentgame.drawGame(world.window);


        world.window.display();


    }






    return 0;
}