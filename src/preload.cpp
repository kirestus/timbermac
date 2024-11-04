#include "headers/preload.h"
#include "headers/GlobalEnums.h"



preload::preload(){
    textureCloud.loadFromFile("graphics\\cloud.png");
    textureBranch.loadFromFile("graphics\\branch.png");
    texturePlayer.loadFromFile("graphics\\player.png");
    textureBee.loadFromFile("graphics\\bee.png");
    textureTree.loadFromFile("graphics\\tree.png");
    textureBackground.loadFromFile("graphics\\background.png");
    textureAxe.loadFromFile("graphics\\axe.png");
    textureLog.loadFromFile("graphics\\log.png");
    textureTombstone.loadFromFile("graphics\\rip.png");


    Player playerCharacter = Player(getTexture(eTextureList::PLAYER),0,0,true,0);
    log = GameObject(getTexture(eTextureList::LOG),3000,0,true);
    backGround = GameObject(getTexture(eTextureList::BACKGROUND), 0, 0, false);
    bee = GameObject(getTexture(eTextureList::BEE), 0, 0, true,sf::Vector2f(0.6f,0.6f),0.0f);
    tree = GameObject(getTexture(eTextureList::TREE), 1280/2,720/2-80, true);
    axe = GameObject(getTexture(eTextureList::AXE),0,0,true);

}

sf::Texture& preload::getTexture(eTextureList _texture)
{

    switch (_texture)
    {
    case  eTextureList::CLOUD:

        return textureCloud;
        break;
    case  eTextureList::BRANCH:
        return textureBranch;
        break;
    case eTextureList::PLAYER:
        return texturePlayer;
        break;
    case eTextureList::BEE:
        return textureBee;
        break;
    case eTextureList::TREE:
        return textureTree;
        break;
    case eTextureList::BACKGROUND:
        return textureBackground;
        break;
    case eTextureList::LOG:
        return textureLog;
        break;
    case eTextureList::AXE:
        return textureAxe;
        break;
    case eTextureList::Tombstone:
        return textureTombstone;
        break;
    default:
        break;
    }

    return textureBackground;
}
