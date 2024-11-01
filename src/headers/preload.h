#pragma once
#include <string>
#include "GameObject.h"
#include "Cloud.h"
#include "Branch.h"
#include "Player.h"
#include "SFML/Audio.hpp"
#include "GlobalEnums.h"


class preload{
private:

std::string graphicsFilePath = "/Users/johnfry/TimberMac/timbermac/graphics/";// i hate having to do this
std::string fontFilePath = "/Users/johnfry/TimberMac/timbermac/fonts/";



sf::Texture textureCloud;
sf::Texture textureBackground;
sf::Texture textureBee;
sf::Texture textureTree;
sf::Texture textureBranch;
sf::Texture texturePlayer;

sf::SoundBuffer deathBuffer;
sf::Sound death;

sf::SoundBuffer pauseBuffer;
sf::Sound pauseJingle; 


sf::SoundBuffer chopBuffer;
sf::Sound chop;


Player playerCharacter;
GameObject backGround;
GameObject tree;
GameObject bee;

public:
preload();
Player getPlayer(){return playerCharacter;}
GameObject* getBackground(){return &backGround;}
GameObject getBee(){return bee;} 
GameObject getTree(){return tree;}

sf::Texture& getTexture(eTextureList _texture)//todo make this an enum
{

    switch (_texture)
    {
    case  eTextureList::CLOUD:     
        textureCloud.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/cloud.png");
        return textureCloud;
        break;
    case  eTextureList::BRANCH:
        textureBranch.loadFromFile(graphicsFilePath+"branch.png");
        return textureBranch;
        break;
    case eTextureList::PLAYER:
        return texturePlayer;
        break;
    case eTextureList::BEE:
        return textureBee;
        break;
    case eTextureList::TREE:
        textureTree.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/tree.png");
        return textureTree;

    default:
        break;
    }

    return textureBackground;
}


sf::Sound& getSFX(eSFX _sfx)
{
    switch(_sfx)
    {
        case eSFX::DEATH:
            deathBuffer.loadFromFile("/Users/johnfry/TimberMac/timbermac/sound/death.wav");
            death.setBuffer(deathBuffer);
            return death;
            break;

        case eSFX::CHOP:
            chopBuffer.loadFromFile("/Users/johnfry/TimberMac/timbermac/sound/chop.wav");
            chop.setBuffer(chopBuffer);
            return chop;
            break;

        case eSFX::PAUSE:
            pauseBuffer.loadFromFile("/Users/johnfry/TimberMac/timbermac/sound/pause.mp3");
            pauseJingle.setBuffer(pauseBuffer);
            return pauseJingle;
            break;

        default:
            break;
    }
return chop;
}

};