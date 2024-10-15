#include <iostream>
#include <string>
#include <sstream>
#include "headers/GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//using namespace sf;


int main()
{

    sf::Vector2i resolution(1280,720);


    srand((int)time(0));

    std::string graphicsFilePath = "/Users/johnfry/TimberMac/timbermac/graphics/";// i hate having to do this
    std::string fontFilePath = "/Users/johnfry/TimberMac/timbermac/fonts/";
    int playerScore = 0;

    

    sf::VideoMode vm(resolution.x, resolution.y);
    sf::RenderWindow window(vm, "Timber",sf::Style::Resize);

    sf::Texture textureBackground;
    textureBackground.loadFromFile(graphicsFilePath+"background.png");

    sf::Texture textureBee;
    textureBee.loadFromFile(graphicsFilePath+"bee.png");

    sf::Texture textureTree;
    textureTree.loadFromFile(graphicsFilePath+"tree.png");

    sf::Texture textureCloud;
    textureCloud.loadFromFile(graphicsFilePath+"cloud.png");

    GameObject backGround = GameObject(textureBackground, 0, 0, false);
    backGround.getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);
    GameObject tree = GameObject(textureTree, resolution.x/2,resolution.y/2-80, true);
    tree.getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);

    GameObject bee = GameObject(textureBee, 0, 0, true);
    bee.getSprite().scale(-1, 1);
    bee.updatePos(300, 100);
    bee.setSpeed(sf::Vector2f(40.0f, 2.0f));


    GameObject cloud = GameObject(textureCloud, 400, 90, true);
    cloud.setSpeed(sf::Vector2f(0.1, 0));
    cloud.getSprite().scale(1.4, 1.6);

    GameObject cloud2 = GameObject(textureCloud, 200, 200, true);
    sf::Vector2f cloudSpeed2(0.3, 0.0f);
    cloud2.setSpeed(cloudSpeed2);


    sf::Clock clockTime;
    bool paused = true;

    //time bar
    sf::RectangleShape timeBar;
    sf::Vector2f timeBarStartSize(400,30);
    timeBar.setSize(timeBarStartSize);
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setOutlineColor(sf::Color::White);
    timeBar.setOutlineThickness(4);
    timeBar.setPosition((resolution.x/2)-timeBarStartSize.x/2,(resolution.y)-timeBarStartSize.y-30);


    sf::Text messageText;
    sf::Text scoreText;

    sf::Font hudFont;
    hudFont.loadFromFile(fontFilePath+"hudFont.ttf");
    scoreText.setFont(hudFont);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(20);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);
    scoreText.setFillColor(sf::Color::White);

    messageText.setFont(hudFont);
    messageText.setString("TIMBER!!!: Press Enter To Start The Game!!");
    messageText.setCharacterSize(30);
    messageText.setFillColor(sf::Color::White);

    //position the text

    sf::FloatRect scoreRect = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreRect.left+scoreRect.width/2.0f,scoreRect.top+scoreRect.height/2.0f);
    scoreText.setPosition(100,30);


    sf::FloatRect messageRect = messageText.getLocalBounds();
    messageText.setOrigin(messageRect.left+messageRect.width/2.0f,messageRect.top+messageRect.height/2.0f);
    messageText.setPosition(resolution.x/2,resolution.y/2);

    bool isBeeActive = false;


    /*///////////////////////////
    GameLoop
    ///////////////////////////*/

    while (window.isOpen())
    {
        window.clear();// clear the screen before drawing the next frame        
        int number = (rand() % 100);
        sf::Time dt = clockTime.restart(); //deltaTime


       /*********************************************************
        Check For User Inputs
        *********************************************************/

       

       sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){window.close();}

            if (event.type == sf::Event::KeyPressed){

                switch (event.key.code)
                {case sf::Keyboard::Escape:
                window.close();
                    break;

                case sf::Keyboard::Enter:
                if (paused){paused=false;}
                
                else if (!paused){paused=true;}
                    break;
                
                case sf::Keyboard::F:
                //playerScore++;
                    break;
                
                default:
                    break;
                }


            }

        } 

        /*********************************************************
        Update the Scene
        *********************************************************/

        std::stringstream ss;
        ss << "Score = " << playerScore;
        scoreText.setString(ss.str());


    if(!paused)
    {
        
       if (!isBeeActive)
       {
            bee.updatePos(-100, 100+number*3);
            bee.setSpeed(sf::Vector2f(number/10+20, 2.0f));

            isBeeActive=true;

       }
       if (bee.getPos().x>resolution.x+100){
        isBeeActive = false;
       }


        cloud2.move(cloud2.getSpeed(),dt.asSeconds());
        cloud.move(cloud.getSpeed(),dt.asSeconds());
        bee.move(bee.getSpeed(),dt.asSeconds());
    }

        
        
        
        /*********************************************************
        Draw The Scene
        *********************************************************/
        backGround.drawGO(window);
        cloud2.drawGO(window);
        cloud.drawGO(window);
        tree.drawGO(window);
        bee.drawGO(window);

        if(paused){window.draw(messageText);}

        window.draw(scoreText);
        window.draw(timeBar);
        window.display();
        dt = clockTime.getElapsedTime();

        



        // Track Time
        

    }
}

