#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>
enum class side{LEFT,RIGHT,NONE};

class Branch : public GameObject{
// what side is the player or branch on

    private: 
        int mNumberOfBranches = 6;
        sf::Texture textureBranch;
    
    public:


        Branch();
        Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id); 
        

        void renderBranches(sf::RenderWindow &_window, Branch*);
        void createBranches(int _itter, side);
        void updateBranchPosition(int _seed, side*);

};

