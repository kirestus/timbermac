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

    sf::Vector2f mSpeed;

public:
    GameObject(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite);

    sf::Sprite createSprite(sf::Texture & _texture, float posX, float posY, bool _shouldCenterSprite);   

    sf::Sprite& getSprite() { return this->mSprite;}

    sf::Vector2f getPos();
    
    sf::Vector2f updatePos(float _x,float _y);
    
    void setSpeed(sf::Vector2f _speed) { this->mSpeed = _speed; };

    void move() { this->mSprite.move(this->mSpeed);}

    void drawGO(sf::RenderWindow &_rw){ _rw.draw(this->mSprite);}


    sf::Vector2f getSpeed() { return this-> mSpeed; }
};

