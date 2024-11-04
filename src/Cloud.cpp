
#include "headers/Cloud.h"

Cloud::Cloud(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id) : GameObject(_texture, posX, posY, _shouldCenterSprite){



    if (_id == eBigCloud)
        {setSpeed(sf::Vector2f(1, 0.0));
        getSprite().scale(1.4, 1.6);}

    if (_id == eSmallCloud)
        {setSpeed(sf::Vector2f(1.4, 0.0));
        getSprite().scale(1.0, 1.0);}


}