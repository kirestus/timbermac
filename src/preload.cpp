#include "headers/preload.h"
#include "headers/GlobalEnums.h"



preload::preload(){

    const sf::Vector2f* resolution = &constants::resolution;
    
    Player playerCharacter = Player(getTexture(eTextureList::PLAYER),0,0,true,0);
    log = GameObject(getTexture(eTextureList::LOG),3000,0,true);
    backGround = GameObject(getTexture(eTextureList::BACKGROUND), 0, 0, false);
    bee = GameObject(getTexture(eTextureList::BEE), 0, 0, true,sf::Vector2f(0.6f,0.6f),0.0f);
    tree = GameObject(getTexture(eTextureList::TREE), resolution->x/2,resolution->y/2-80, true);
    axe = GameObject(getTexture(eTextureList::AXE),0,0,true);

}

