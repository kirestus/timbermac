#include "headers/GameObject.h"
//#include <SFML/Graphics.hpp>


GameObject::GameObject(){
    xPos = 0;
    yPos = 0;
    mOrient = 0.0;
    mIsFlopped = false;
}


GameObject::GameObject(sf::Texture& _texture, float posX= 0, float posY= 0, bool _shouldCenterSprite=true) {
    
    mSprite = createSprite(_texture, posX, posY, _shouldCenterSprite, sf::Vector2f(1.0f,1.0f),0.0f);
    xPos = posX;
    yPos = posY;
    mOrient = getOrient();
    mIsFlopped = false;
}

GameObject::GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite=true, sf::Vector2f _scale=sf::Vector2f(1.0f,1.0f), float _orient=0.0f){
    mSprite = this->createSprite(_texture, posX, posY, _shouldCenterSprite, _scale,_orient);
    xPos = posX;
    yPos = posY;
    mOrient = _orient;
    mIsFlopped = false;
    mScale = _scale;
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
    xPos = _x;
    yPos = _y;

    mSprite.setPosition(_x, _y);
    return sf::Vector2f(_x, _y);
}

void GameObject::move(sf::Vector2f _speed, sf::Time &_dt){
    float activeTime= _dt.asSeconds();
    if (getIsFlopped())
    {
        //if the sprite is flipped inverse the speed of the translation, this way forwards is always forwards
        mSprite.move(_speed = sf::Vector2f((_speed.x *= -1)*activeTime,mSpeed.y*activeTime));
        return;
    }
    else{
        sf::Vector2f vSpeed;
        vSpeed.x = getSpeed().x; vSpeed.y = getSpeed().y;
        this->mSprite.move(_speed = sf::Vector2f(_speed.x*activeTime,mSpeed.y*activeTime));
        }
    return;
     
     }




const sf::Vector2f GameObject::getPos() { return this->getSprite().getPosition();}

const float GameObject::getOrient(){return this->getSprite().getRotation();}

