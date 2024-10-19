#include "headers/GameObject.h"
//#include <SFML/Graphics.hpp>


GameObject::GameObject(){

    
}

GameObject::GameObject(sf::Texture& _texture, float posX= 0, float posY= 0, bool _shouldCenterSprite=true) {
    
    this->mSprite = this->createSprite(_texture, posX, posY, _shouldCenterSprite, sf::Vector2f(1.0f,1.0f),0.0f);
    this->xPos = posX;
    this->yPos = posY;
    this->mOrient = this->getOrient();
    this->mIsFlopped = false;
}

GameObject::GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite=true, sf::Vector2f _scale=sf::Vector2f(1.0f,1.0f), float _orient=0.0f){
    this->mSprite = this->createSprite(_texture, posX, posY, _shouldCenterSprite, _scale,_orient);
    this->xPos = posX;
    this->yPos = posY;
    this->mOrient = _orient;
    this->mIsFlopped = false;
    this->mScale = _scale;
}  


sf::Sprite GameObject::createSprite(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, sf::Vector2f _scale, float _orient=0) {
    sf::Sprite sprite;
    sprite.setTexture(_texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(_scale);
    sprite.setRotation(_orient);
    if (_shouldCenterSprite == true) { sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2); } // find the center of the bee and set its origin
    return sprite;

}


sf::Vector2f GameObject::updatePos(float _x, float _y) {
    this->xPos = _x;
    this->yPos = _y;

    this->getSprite().setPosition(_x, _y);
    return sf::Vector2f(_x, _y);
}

void GameObject::move(sf::Vector2f _speed, sf::Time &_dt){
    float activeTime= _dt.asSeconds();
    if (this->getIsFlopped())
    {
        //if the sprite is flipped inverse the speed of the translation, this way forwards is always forwards
        this->mSprite.move(_speed = sf::Vector2f((_speed.x *= -1)*activeTime,mSpeed.y*activeTime));
        return;
    }
    else{
        sf::Vector2f vSpeed;
        vSpeed.x = this->getSpeed().x; vSpeed.y = this->getSpeed().y;
        this->mSprite.move(_speed = sf::Vector2f(_speed.x*activeTime,mSpeed.y*activeTime));
        }
    return;
     
     }




sf::Vector2f GameObject::getPos() { return this->getSprite().getPosition();}

float GameObject::getOrient(){return this->getSprite().getRotation();}

