#include "headers/Player.h"

Player::Player(){
}

Player::Player(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id)
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){
    getSprite().setTexture(_texture);
}


void Player::sidePosition()
{
    const int xSideOffset =110;
    const int yPos = 400;
    if (!getIsDead())
    {
        if (getPlayerSide() == side::LEFT)
        {
            updatePos(constants::screenCenter.x-xSideOffset,yPos);
            getSprite().setScale(sf::Vector2f(-1,1));

        }
        else if (getPlayerSide() == side::RIGHT)
        {
            updatePos(constants::screenCenter.x+xSideOffset,yPos);
            getSprite().setScale(sf::Vector2f(1,1));
        }
        else 
            updatePos(3000,3000);//move him off to the middle of nowhere
    }
}

void Player::dead(sf::Texture& _tombstoneTexture){
    getSprite().setTexture(_tombstoneTexture);
    updatePos(getPos().x,getPos().y+50);
    setIsDead(true);
}

void Player::alive(sf::Texture& _playerTexture){
    getSprite().setTexture(_playerTexture);
    setPlayerSide(side::LEFT);
    getSprite().setScale(sf::Vector2f(-1,1));
    setIsDead(false);
    sidePosition();
}
void Player::swingAxe(bool _shouldSwing, GameObject& _axe){
    if (_shouldSwing == true){
        _axe.updatePos(this->getPos().x,this->getPos().y+100);
    }

}