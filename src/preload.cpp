#include "headers/preload.h"
#include "headers/GlobalEnums.h"



preload::preload(){

    const sf::Vector2f resolution(1280,720);

    textureBackground.loadFromFile(graphicsFilePath+"background.png");
    textureBee.loadFromFile(graphicsFilePath+"bee.png");
    textureTree.loadFromFile(graphicsFilePath+"tree.png");
    textureCloud.loadFromFile(graphicsFilePath+"cloud.png");
    textureBranch.loadFromFile(graphicsFilePath+"branch.png");
    texturePlayer.loadFromFile(graphicsFilePath+"player.png");
    //todo set these up with pointers later on
    
   

    
    Player playerCharacter = Player(getTexture(eTextureList::PLAYER),0,0,true,0);
    backGround = GameObject(getTexture(eTextureList::BACKGROUND), 0, 0, false);
    bee = GameObject(getTexture(eTextureList::BEE), 0, 0, true,sf::Vector2f(0.6f,0.6f),0.0f);
    tree = GameObject(getTexture(eTextureList::TREE), resolution.x/2,resolution.y/2-80, true);

}

