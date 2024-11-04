#include <iostream>
#include <string>
#include <sstream>
#include "headers/GlobalEnums.h"
#include "headers/preload.h"
#include "headers/GameObject.h"
#include "headers/Cloud.h"
#include "headers/Branch.h"
#include "headers/Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




bool paused = true;
bool queuePause = false;


// i need to chunk this shit out into its own class, im sick of it gumming up my main
void centerText(sf::Text &_textObj, sf::Vector2f _pos = constants::resolution){

    sf::FloatRect _boundingRect = _textObj.getLocalBounds();
    _textObj.setOrigin(_boundingRect.left+_boundingRect.width/2.0f,_boundingRect.top+_boundingRect.height/2.0f);
    
    if(_pos == constants::resolution){_pos.x /= 2; _pos.y /= 2;}

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


void moveLog(GameObject* _logGO, bool _logActive, sf::Time& _dt, side _playerSide,side _cachedPlayerSide){
    if (_logActive){
        float rotValue = _logGO->getOrient();
        if(_cachedPlayerSide == side::LEFT){
            _logGO->move(sf::Vector2f(5000.0,0),_dt);
            _logGO->getSprite().rotate(rotValue+=10);
        }
        else{_logGO->move(sf::Vector2f(-5000.0,0),_dt);
            _logGO->getSprite().rotate(rotValue+=10);
            }
        if(_logGO->getPos().x>2000 || _logGO->getPos().x<-2000){//if the log goes to far disable it
            _logActive = false;
        }
    }
}

void playerDeath(Player* _playerCharacter, Branch* _branchesGO, side* _branchSide, sf::Sound* _deathSound, sf::Texture* _tombstoneTexture)
{
    if(_playerCharacter->getPlayerSide() == _branchesGO->getLethalBranch(_branchesGO,_branchSide,constants::numberOfBranches)){
        if(_playerCharacter->getPlayerSide()!= side::NONE){
            _playerCharacter->dead(*_tombstoneTexture);
            _deathSound->play();
            queuePause = true;                               
        }  
    }
}


int main()
{

    preload loadGame;//runs a preload
    preload* getData = &loadGame;

    Player* playerCharacter = getData->getPlayerPtr();
    GameObject* backgroundGO = getData->getGO(eGO::BACKGROUND);
    GameObject* beeGO = getData->getGO(eGO::BEE);
    GameObject* treeGO = getData->getGO(eGO::TREE);
    GameObject* logGO = getData->getGO(eGO::LOG);
    side eSideOfBranches[constants::numberOfBranches];
    Branch branchesGO[constants::numberOfBranches]; // initiate branchesGO
    GameObject* axeGO = getData->getGO(eGO::AXE);

    sf::Sound* pauseSound = &getData->getSFX(eSFX::PAUSE);
    sf::Sound* deathSound = &getData->getSFX(eSFX::DEATH);
    sf::Sound* chopSound = &getData->getSFX(eSFX::CHOP);

    //variables 
    srand((int)time(0));
    
    int playerScore = 0;
    const float gameLoopTime = 12;
    float timeRemaining = gameLoopTime;

    sf::VideoMode const vm(1280, 
        720);
    sf::RenderWindow window(vm, "Timber",sf::Style::Resize);
    
    sf::Clock clockTime;
    int cacheUpdate = 0;;


    //time bar
    sf::RectangleShape timeBar;
    sf::Vector2f timeBarStartSize(400,30);
    timeBar.setSize(timeBarStartSize);
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setOutlineColor(sf::Color::White);
    timeBar.setOutlineThickness(4);
    timeBar.setPosition((constants::resolution.x/2)-timeBarStartSize.x/2,(constants::resolution.y)-timeBarStartSize.y-30);
    float timeBarWidthPerSecond = timeBarStartSize.x / timeRemaining;

    sf::Text messageText;
    sf::Text scoreText;


    sf::Font* hudFont = getData->getHudFont();
    scoreText.setFont(*hudFont);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(20);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);
    scoreText.setFillColor(sf::Color::White);

    messageText.setFont(*hudFont);
    messageText.setString("TIMBER!!!: Press Enter To Start The Game!!");
    messageText.setCharacterSize(30);
    messageText.setFillColor(sf::Color::White);

    treeGO->updatePos(constants::screenCenter.x, constants::screenCenter.y-80);


//initiate all the gameobjects
    backgroundGO->getSprite().scale(float(constants::resolution.x)/1920,float(constants::resolution.y)/1080);//this is weak i should do this in the go class
    treeGO->getSprite().scale(float(constants::resolution.x)/1920,float(constants::resolution.y)/1080);

    beeGO->flopGO();
    beeGO->setSpeed(sf::Vector2f(-40.0f, 2.0f));
    bool isBeeActive = false;

    playerCharacter->alive(getData->getTexture(eTextureList::PLAYER));
    playerCharacter->sidePosition();
    side cachedPlayerSide = playerCharacter->getPlayerSide();//set the players starting side and cache it


    //todo make these into an array and spawn them in random locations
    Cloud cloud = Cloud(getData->getTexture(eTextureList::CLOUD), 400, 200, true, cloud.eBigCloud); 
    Cloud cloud2 = Cloud(getData->getTexture(eTextureList::CLOUD), 100,103, true, cloud.eSmallCloud);
    Cloud cloud3 = Cloud(getData->getTexture(eTextureList::CLOUD), 760,245, true, cloud.eSmallCloud);

    //position the text
    centerText(scoreText,sf::Vector2f(100,30));
    centerText(messageText);

    for (int i = 0; i < constants::numberOfBranches; ++i) 
    {
        branchesGO[i] = Branch(getData->getTexture(eTextureList::BRANCH), 0, 0, true, i);
        branchesGO->updateBranchPosition(branchesGO,eSideOfBranches,constants::numberOfBranches,i);
    }

    bool logIsActive=false;
    int numberOfUpdates = 0;//keeps track of the current frame number
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
                    branchesGO->updateBranchPosition(branchesGO,eSideOfBranches,constants::numberOfBranches, number);
                    playerScore =0;
                    playerCharacter->alive(getData->getTexture(eTextureList::PLAYER));
                    numberOfUpdates = 0;
                    }
                
                else if (!paused){paused=true;
                    updateText(messageText,"Paused...");
                    pauseSound->play();
                    branchesGO->resetBranches(branchesGO,eSideOfBranches,constants::numberOfBranches);
                }
                    break;
                
                case sf::Keyboard::A: case sf::Keyboard::Left:
                    if(!paused){
                        if (playerCharacter->getPlayerSide() != side::LEFT){
                            playerCharacter->setPlayerSide(side::LEFT);
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
                            playerDeath(playerCharacter,branchesGO,eSideOfBranches,deathSound, &getData->getTexture(eTextureList::Tombstone));
                            if (!queuePause){
                                playerCharacter->swingAxe(true, *axeGO);
                                cacheUpdate = numberOfUpdates;
                                branchesGO->cutLowestBranch(branchesGO,eSideOfBranches,constants::numberOfBranches,logIsActive);}
                                chopSound->play();
                                cachedPlayerSide = playerCharacter->getPlayerSide();
                                branchesGO->updateBranchPosition(branchesGO,eSideOfBranches,constants::numberOfBranches,number+playerScore);
                                playerScore++;
                                logGO->updatePos(constants::resolution.x/2,450);
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
        pauseSound->pause();
        for (int i = 0; i < constants::numberOfBranches; i++){
            branchesGO[i].moveBranch(branchesGO, eSideOfBranches, i); 
         }

       if (!isBeeActive){
            beeGO->updatePos(-100, float(100+number*3));
            beeGO->setSpeed(sf::Vector2f(number*12%100*-1,0));
            isBeeActive=true;
       }
       if (beeGO->getPos().x>constants::resolution.x+100){
            isBeeActive = false;
       }

        cloud2.move(cloud2.getSpeed(),dt);
        cloud.move(cloud.getSpeed(),dt);
        cloud3.move(cloud3.getSpeed(),dt);
        beeGO->move(beeGO->getSpeed(),dt);
        moveLog(logGO,logIsActive,dt,playerCharacter->getPlayerSide(),cachedPlayerSide);
        numberOfUpdates ++; 

    }// end if(!paused)

        /*********************************************************
        Draw The Scene
        *********************************************************/
        backgroundGO->drawGO(window);

        cloud3.drawGO(window);
        cloud2.drawGO(window);
        cloud.drawGO(window);
        
        if(numberOfUpdates>1){branchesGO->renderBranches(window,branchesGO,constants::numberOfBranches);}
        treeGO->drawGO(window);
        if(numberOfUpdates>1){beeGO->drawGO(window);}
        if (!paused){logGO->drawGO(window);}
        playerCharacter->drawGO(window);
        if(numberOfUpdates<cacheUpdate+130){axeGO->drawGO(window);}//axe hit only lasts a moment
        if(paused){
            window.draw(messageText);
            timeRemaining = gameLoopTime;
        }
        //draw hud elements last
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

