#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>

class GameObject
{
private:
    sf::Sprite mSprite;
    sf::Vector2f mScale;
    float xPos;
    float yPos;
    float mOrient;
    bool mIsFlopped;

    bool mIsPysicsObject;
    bool mHasHitBox;

    sf::Vector2f mSpeed;

public:

    GameObject();
    GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite);
    GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, sf::Vector2f _scale, float _orient);  
    
    sf::Sprite createSprite(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, sf::Vector2f _scale, float _orient);   
    sf::Sprite& getSprite() { return this->mSprite;}

    
    const sf::Vector2f getPos();
    const float getOrient();
    const bool getIsFlopped(){return this->mIsFlopped;}
    const sf::Vector2f getSpeed() { return this-> mSpeed; }    

    sf::Vector2f updatePos(float _x,float _y);
    void setSpeed(sf::Vector2f _speed) { this->mSpeed = _speed; };

    void move(sf::Vector2f _speed, sf::Time &_dt);
    void setFlopped(){this->mIsFlopped=true;}

    void drawGO(sf::RenderWindow &_rw);

    void flopGO();



};

