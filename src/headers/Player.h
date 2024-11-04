#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "GlobalEnums.h"


class Player : public GameObject{

private:
    side m_ePLayerSide = side::LEFT;
    bool mIsDead=false;



public:
    
    Player();
    Player(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id); 

    void sidePosition();
    void dead(sf::Texture& _tombStoneTexture);
    void alive(sf::Texture& _playerTexture);

    void swingAxe(bool _shouldSwing, GameObject& _axe);

    side getPlayerSide(){return m_ePLayerSide;}
    void setPlayerSide(side _ePlayerSide){m_ePLayerSide =_ePlayerSide;}

    bool getIsDead(){return mIsDead;}
    void setIsDead(bool _isDead){mIsDead = _isDead;}


};

