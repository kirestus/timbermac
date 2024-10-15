#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include<string>

class GameObject
{
private:
    sf::Sprite mSprite;
    float xPos;
    float yPos;
    float mOrient;
    bool mIsFlopped;

    bool mIsPysicsObject;
    bool mHasHitBox;

    sf::Vector2f mSpeed;

public:

    GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite);
    sf::Sprite createSprite(sf::Texture & _texture, float posX, float posY, bool _shouldCenterSprite);   
    sf::Sprite& getSprite() { return this->mSprite;}

    
    sf::Vector2f getPos();
    float getOrient();
    bool getIsFlopped(){return this->mIsFlopped;}
    sf::Vector2f getSpeed() { return this-> mSpeed; }    

    sf::Vector2f updatePos(float _x,float _y);
    void setSpeed(sf::Vector2f _speed) { this->mSpeed = _speed; };

    void move(sf::Vector2f _speed, float _dt);
    void setFlopped(){this->mIsFlopped=true;}

    void drawGO(sf::RenderWindow &_rw){ _rw.draw(this->mSprite);}



};

