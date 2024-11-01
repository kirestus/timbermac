#include <iostream>
#include <string>
#include <sstream>
#include "headers/GlobalEnums.h"
#include "headers/GameObject.h"
#include "headers/Cloud.h"
#include "headers/Branch.h"
#include "headers/Player.h"
#include "headers/preload.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

preload loadGame;//runs a preload
preload* getData = &loadGame;

const sf::Vector2f resolution(1280,720);

const int numberOfBranches = 6;
side eSideOfBranches[numberOfBranches];
Branch branches[numberOfBranches]; // initiate branches

// i need to chunk this shit out into its own class, im sick of it gumming up my main
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
    std::string fontFilePath = "/Users/johnfry/TimberMac/timbermac/fonts/";
    
    int playerScore = 0;
    const float gameLoopTime = 12;
    float timeRemaining = gameLoopTime;

    sf::VideoMode vm(resolution.x, resolution.y);
    sf::RenderWindow window(vm, "Timber",sf::Style::Resize);

    
    sf::Clock clockTime;
    bool paused = true;
    bool queuePause = false;

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


    sf::Sound* pauseSound = &getData->getSFX(eSFX::PAUSE);
    sf::Sound* deathSound = &getData->getSFX(eSFX::DEATH);
    sf::Sound* chopSound = &getData->getSFX(eSFX::CHOP);

    Player* playerCharacter = getData->getPlayerPtr();
    GameObject* backGround = getData->getGO(eGO::BACKGROUND);
    GameObject* beeGO = getData->getGO(eGO::BEE);
    GameObject* treeGO = getData->getGO(eGO::TREE);

    backGround->getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);//this is weak i should do this in the go class
    treeGO->getSprite().scale(float(resolution.x)/1920,float(resolution.y)/1080);

    beeGO->flopGO();
    beeGO->setSpeed(sf::Vector2f(-40.0f, 2.0f));
    bool isBeeActive = false;

    playerCharacter->sidePosition();


    //todo make these into an array and spawn them in random locations
    Cloud cloud = Cloud(getData->getTexture(eTextureList::CLOUD), 400, 200, true, cloud.eBigCloud); 
    Cloud cloud2 = Cloud(getData->getTexture(eTextureList::CLOUD), 100,103, true, cloud.eSmallCloud);
    Cloud cloud3 = Cloud(getData->getTexture(eTextureList::CLOUD), 760,245, true, cloud.eSmallCloud);

    //position the text
    centerText(scoreText,sf::Vector2f(100,30));
    centerText(messageText);

    for (int i = 0; i < numberOfBranches; ++i) 
    {
        branches[i] = Branch(getData->getTexture(eTextureList::BRANCH), 0, 0, true, i);
        branches->updateBranchPosition(branches,eSideOfBranches,numberOfBranches,i);
    }

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

       bool lockInput = false;

       sf::Event event; 
       // need to chunk this out into its own class eventually so my code is so gummed up
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){window.close();}

            if (event.type == sf::Event::KeyReleased){
                switch (event.key.code)
                {case sf::Keyboard::Space:
                lockInput = false;
                    break;
                default:
                    break;
                }

            }
            if (event.type == sf::Event::KeyPressed){

                switch (event.key.code)
                {case sf::Keyboard::Escape:
                window.close();
                    break;

                case sf::Keyboard::Enter:
                if (paused){
                    paused=false;
                    branches->updateBranchPosition(branches,eSideOfBranches,numberOfBranches, number);
                    playerScore =0;
                    playerCharacter->alive();
                    }
                
                else if (!paused){paused=true;
                    updateText(messageText,"Paused...");
                    pauseSound->play();
                    branches->resetBranches(branches,eSideOfBranches,numberOfBranches);

                }
                    break;
                
                case sf::Keyboard::A: case sf::Keyboard::Left:
                    if(!paused){
                        if (playerCharacter->getPlayerSide() != side::LEFT){
                            playerCharacter->setPlayerSide(side::LEFT);
                            ///if branch 6 side = playerside kill player
                            playerCharacter->sidePosition();
                        }
                    }
                    break;

                case sf::Keyboard::D: case sf::Keyboard::Right:
                    if(!paused){
                        if (playerCharacter->getPlayerSide() != side::RIGHT){
                            playerCharacter->setPlayerSide(side::RIGHT);
                            playerCharacter->sidePosition();
                        }
                    }
                    break;

                case sf::Keyboard::Space:
                    if(!paused){
                        if (playerCharacter->getIsDead()== false && lockInput != true){
                            if(playerCharacter->getPlayerSide() == branches->getLethalBranch(branches,eSideOfBranches,numberOfBranches)){
                                if(playerCharacter->getPlayerSide()!= side::NONE)//going a litte deep on the if statments here, should try and break it up a bit
                                {playerCharacter->dead();
                                    deathSound->play();
                                    queuePause = true;       
                                }  
                            }
                            chopSound->play();
                            branches->updateBranchPosition(branches,eSideOfBranches,numberOfBranches,number+playerScore);
                            playerScore++;
                        }
                       lockInput = true;
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
        //branches->updateBranchPosition(branches,eSideOfBranches,numberOfBranches);
        pauseSound->pause();
        for (int i = 0; i < numberOfBranches; i++){
            branches[i].moveBranch(branches, eSideOfBranches, i); 
         }

       if (!isBeeActive){
            beeGO->updatePos(-100, 100+number*3);
            beeGO->setSpeed(sf::Vector2f(number*12%100*-1,0));
            isBeeActive=true;
       }
       if (beeGO->getPos().x>resolution.x+100){
        isBeeActive = false;
       }

        cloud2.move(cloud2.getSpeed(),dt);
        cloud.move(cloud.getSpeed(),dt);
        cloud3.move(cloud3.getSpeed(),dt);
        beeGO->move(beeGO->getSpeed(),dt);

    }// end if(!paused)

        /*********************************************************
        Draw The Scene
        *********************************************************/
        backGround->drawGO(window);

        cloud3.drawGO(window);
        cloud2.drawGO(window);
        cloud.drawGO(window);
        branches->renderBranches(window,branches,numberOfBranches);
        treeGO->drawGO(window);
        beeGO->drawGO(window);
        playerCharacter->drawGO(window);



        if(paused){
            window.draw(messageText);
            timeRemaining = gameLoopTime;
        }

        window.draw(scoreText);
        window.draw(timeBar);
        window.display();
        dt = clockTime.getElapsedTime();//keeps track of time

        if (queuePause){//this is just to let the game update the render before pausing so that you can see the player get skewered
                paused=true;
                queuePause=false;
            }
    }
}

