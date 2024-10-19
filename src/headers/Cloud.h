#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

class Cloud : public GameObject
{
    //const std::string graphicsFilePath = "/Users/johnfry/TimberMac/timbermac/graphics/";// i hate having to do this
    public:  
     
     enum cloudType
    {
        eBigCloud,
        eSmallCloud};
    
    Cloud(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id);

        
};
