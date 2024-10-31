#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "GlobalEnums.h"

class Branch : public GameObject{
// what side is the player or branch on

    private: 
        int mNumberOfBranches = 6;
        sf::Texture textureBranch;
    
    public:

        Branch();
        Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id); 
        

        void renderBranches(sf::RenderWindow &_window, Branch*, int _numberOfBranches);
        void moveBranch(Branch* _branch, side* _eBranchPos, int _index);
        void updateBranchPosition(int _seed, int, side* _eBranchPos);
        void resetBranches(Branch* _branch, side* _eBranchPos, int _numberOfBranches);

};

