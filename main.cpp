#include <SFML/Graphics.hpp>
#include <iostream> // Needed for sf::Keyboard




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
    const int BORDER_X = 0;
    const int BORDER_Y = 0;
    const int BOARD_SIZE = 9;

    sf::Vector2i StoneLocations[BOARD_SIZE][BOARD_SIZE]; // stores the pices locations.
    sf::Vector3i THStoneLocations[BOARD_SIZE][BOARD_SIZE]; // stores the pices locations. Have to use 3i because i want to save 3d coords into this vector. x, y and side :)
    int side = 1; // white 1  black 2.

    sf::RenderWindow window(sf::VideoMode(800   , 600), "Go");
    int aspectRatio = 800 / 600;
    int borderIncrease = 5;
   // sf::View view(sf::Vector2f(200.0f, 150.0f), sf::Vector2f(400.0f, 300.0f)); // Controls the views center position and size. Currently a zoomed view.
     sf::View view = window.getView();
     view.setCenter(sf::Vector2f(200, 150));
     view.setSize(sf::Vector2f(400+borderIncrease*aspectRatio, 300+borderIncrease));
         //sf::Vector2(800, 600)));
    //view.zoom(0.5);

    //sf::View view = window.getView();

    sf::RectangleShape player(sf::Vector2f(160,270));
    sf::RectangleShape board(sf::Vector2f(171, 171)); // Board texture size
    sf::RectangleShape black(sf::Vector2f(19, 19)); // stone texture size.
    sf::RectangleShape white(sf::Vector2f(19, 19));


    sf::Texture pieceTexture;
    pieceTexture.loadFromFile("Sprites/Black_white.png");

    black.setTexture(&pieceTexture); //here we set the texture eventhough its the whole texture
    white.setTexture(&pieceTexture); //here we set the texture eventhough its the whole texture



    sf::Vector2u pieceTextureSize = pieceTexture.getSize();
    //here we split the texture into pieces.
    pieceTextureSize.x /= 2; 
    pieceTextureSize.y /= 1; //because only one row :)

    //Get a sub texture from the collected texture Black_white.png
    black.setTextureRect(sf::IntRect(pieceTextureSize.x, 0, pieceTextureSize.x, pieceTextureSize.y)); //First two parameters are the starting positions in the texture and the other two parameters are the size of the texture
    white.setTextureRect(sf::IntRect(0, 0, pieceTextureSize.x, pieceTextureSize.y)); 
    //black.setPosition(0,0);
    //white.setPosition(pieceTextureSize.x, 0);


    player.setPosition(356, 206);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Sprites/toadP.png");
    player.setTexture(&playerTexture);

    board.setPosition(BORDER_X, BORDER_Y);
    sf::Texture boardTexture;
    boardTexture.loadFromFile("Sprites/9x9_board.png");
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





        // drawing code. //maybe only draw when board updates?
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

    return 0;
}