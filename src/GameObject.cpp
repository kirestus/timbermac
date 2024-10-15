#include "headers/GameObject.h"
//#include <SFML/Graphics.hpp>


GameObject::GameObject(sf::Texture& _texture, float posX= 0, float posY= 0, bool _shouldCenterSprite=true) {
    
    this->mSprite = this->createSprite(_texture, posX, posY, _shouldCenterSprite);
    this->xPos = posX;
    this->yPos = posY;
    this->mOrient = this->getOrient();
    this->mIsFlopped = false;
}

sf::Sprite GameObject::createSprite(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite) {
    sf::Sprite sprite;
    sprite.setTexture(_texture);
    sprite.setPosition(posX, posY);
    if (_shouldCenterSprite == true) { sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2); } // find the center of the bee and set its origin
    return sprite;

}

sf::Vector2f GameObject::updatePos(float _x, float _y) {
    this->xPos = _x;
    this->yPos = _y;

    this->getSprite().setPosition(_x, _y);
    return sf::Vector2f(_x, _y);
}

void GameObject::move(sf::Vector2f _speed, float _dt){
    if (this->getIsFlopped())
    {
        //if the sprite is flipped inverse the speed of the translation, this way forwards is always forwards
        this->mSprite.move(_speed = sf::Vector2f(_speed.x *= -1,mSpeed.y));
        return;
    }
    else{
        sf::Vector2f vSpeed;
        vSpeed.x = this->getSpeed().x; vSpeed.y = this->getSpeed().y;
        this->mSprite.move(vSpeed.x * _dt,vSpeed.y * _dt);
        }
    return;
     
     }




sf::Vector2f GameObject::getPos() { return this->getSprite().getPosition();}

float GameObject::getOrient(){return this->getSprite().getRotation();}

