#include "headers/Player.h"


Player::Player(){
texturePlayer.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/player.png");  
textureTombStone.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/rip.png");
}

Player::Player(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id)
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){

texturePlayer.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/player.png"); 
textureTombStone.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/rip.png");
}

void Player::sidePosition()
{
    if (!getIsDead())
    {
        if (getPlayerSide() == side::LEFT)
        {
            updatePos(500,400);
            getSprite().setScale(sf::Vector2f(-1,1));

        }
        else if (getPlayerSide() == side::RIGHT)
        {
            updatePos(750,400);
            getSprite().setScale(sf::Vector2f(1,1));
        }
        else 
            updatePos(3000,3000);
    }
}

void Player::dead(){
    getSprite().setTexture(textureTombStone);
    setIsDead(true);
}

void Player::alive(){
    getSprite().setTexture(texturePlayer);
    setPlayerSide(side::LEFT);
     updatePos(500,400);
    getSprite().setScale(sf::Vector2f(-1,1));
    setIsDead(false);
}