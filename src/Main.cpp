#include <iostream>
#include <string>
#include <sstream>
#include "headers/GlobalEnums.h"
#include "headers/GameObject.h"
#include "headers/Cloud.h"
#include "headers/Branch.h"
#include "headers/Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const int numberOfBranches = 6;
side eSideOfBranches[numberOfBranches];
const sf::Vector2f resolution(1280,720);
Branch branches[numberOfBranches]; // initiate branches
void centerText(sf::Text &_textObj, sf::Vector2f _pos = resolution){

    sf::FloatRect _boundingRect = _textObj.getLocalBounds();
    _textObj.setOrigin(_boundingRect.left+_boundingRect.width/2.0f,_boundingRect.top+_boundingRect.height/2.0f);
    
    if(_pos == resolution){_pos.x /= 2; _pos.y /= 2;}

    _textObj.setPosition(_pos);
    return;
}

void updateText(sf::Text &_textObj, std::string _textStr,sf::Vector2f _pos=sf::Vector2f())
{   
    if(_pos == sf::Vector2f())
    {
        //if vector is not assigned just assume they want to use the current position of the text object
         _pos = _textObj.getPosition();
    }
    _textObj.setString(_textStr);
    centerText(_textObj,_pos);
}


int main()
{
    srand((int)time(0));

    std::string graphicsFilePath = "/Users/johnfry/TimberMac/timbermac/graphics/";// i hate having to do this
    std::string fontFilePath = "/Users/johnfry/TimberMac/timbermac/fonts/";
    
    int playerScore = 0;

    const float gameLoopTime = 6;
    float timeRemaining = gameLoopTime;

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

    sf::Texture textureBranch;
    textureBranch.loadFromFile(graphicsFilePath+"branch.png");

    sf::Texture texturePlayer;
    texturePlayer.loadFromFile(graphicsFilePath+"player.png");

    GameObject backGround = GameObject(textureBackground, 0, 0, false);
    backGround.getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);

    GameObject tree = GameObject(textureTree, resolution.x/2,resolution.y/2-80, true);
    tree.getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);

    GameObject bee = GameObject(textureBee, 0, 0, true,sf::Vector2f(0.6f,0.6f),0.0f);
    bee.flopGO();
    bee.setSpeed(sf::Vector2f(-40.0f, 2.0f));

    Cloud cloud = Cloud(textureCloud, 400, 200, true, cloud.eBigCloud); 
    Cloud cloud2 = Cloud(textureCloud, 100,103, true, cloud.eSmallCloud);
    Cloud cloud3 = Cloud(textureCloud, 760,245, true, cloud.eSmallCloud);

    Player playerCharacter = Player(texturePlayer,0,0,true,0);

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
    float timeBarWidthPerSecond = timeBarStartSize.x / timeRemaining;


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

    playerCharacter.sidePosition();

    //position the text

    centerText(scoreText,sf::Vector2f(100,30));
    centerText(messageText);

    bool isBeeActive = false;

    for (int i = 0; i < numberOfBranches; ++i) 
    {
        branches[i] = Branch(textureBranch, 0, 0, true, i);
        branches[i].updateBranchPosition(i, numberOfBranches, eSideOfBranches);
    }
    //branches->updateBranchPosition

    //branches->resetBranches(branches,eSideOfBranches,numberOfBranches);


    /*///////////////////////////
    GameLoop
    ///////////////////////////*/

    while (window.isOpen())
    {
        window.clear();// clear the screen before drawing the next frame        
        int number = (rand() % 100);
        sf::Time dt = clockTime.restart(); //deltaTime


        //set the timebar size
        timeRemaining -= dt.asSeconds();
        timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarStartSize.y));
        if (timeRemaining <= 0){paused = true;
            updateText(messageText,"Out of Time");
        }


       /*********************************************************
        Check For User Inputs
        *********************************************************/

       

       sf::Event event; 
       // need to chunk this out into its own class eventually so my code is so gummed up
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
                
                else if (!paused){paused=true;
                    updateText(messageText,"Paused...");
                }
                    break;
                
                case sf::Keyboard::A:
                    if(!paused)
                    {
                        if (playerCharacter.getPlayerSide() == side::RIGHT)
                        {
                            playerCharacter.setPlayerSide(side::LEFT);
                            playerCharacter.sidePosition();
                        }
                    }
                    break;

                case sf::Keyboard::D:
                    if(!paused)
                    {
                        if (playerCharacter.getPlayerSide() == side::LEFT)
                        {
                            playerCharacter.setPlayerSide(side::RIGHT);
                            playerCharacter.sidePosition();
                        }
                    }
                    break;

                case sf::Keyboard::P:
                    if(!paused)
                    {
                        if (playerCharacter.getIsDead()== false)
                        {
                            playerCharacter.setIsDead(true);
                            playerCharacter.dead();
                        }
                    }
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
        for (int i = 0; i < numberOfBranches; i++)
        {
            branches[i].moveBranch(branches, eSideOfBranches, i); 
         }

       if (!isBeeActive)
       {
            bee.updatePos(-100, 100+number*3);
            bee.setSpeed(sf::Vector2f(number*-12,0));

            isBeeActive=true;

       }
       if (bee.getPos().x>resolution.x+100){
        isBeeActive = false;
       }


        cloud2.move(cloud2.getSpeed(),dt);
        cloud.move(cloud.getSpeed(),dt);
        cloud3.move(cloud3.getSpeed(),dt);

        bee.move(bee.getSpeed(),dt);


    }// end if(!paused)

        
        /*********************************************************
        Draw The Scene
        *********************************************************/
        backGround.drawGO(window);

        cloud3.drawGO(window);
        cloud2.drawGO(window);
        cloud.drawGO(window);
        branches->renderBranches(window,branches,numberOfBranches);
        tree.drawGO(window);
        bee.drawGO(window);

        playerCharacter.drawGO(window);



        if(paused){
            window.draw(messageText);
            playerScore = 0;
            timeRemaining = 6;
        }

        window.draw(scoreText);
        window.draw(timeBar);
        window.display();
        dt = clockTime.getElapsedTime();

        // Track Time
        

    }
}

