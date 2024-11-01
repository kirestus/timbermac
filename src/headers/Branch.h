#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "GlobalEnums.h"

class Branch : public GameObject{
// what side is the player or branch on

    private: 
        const int* mNumberOfBranches = &constants::numberOfBranches;
        sf::Texture textureBranch;
        side mBranchSide =side::NONE;

    
    public:

        Branch();
        Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id); 
        

        void renderBranches(sf::RenderWindow &_window, Branch*, int _numberOfBranches);
        void moveBranch(Branch* _branch, side* _eBranchPos, int _index);
        void updateBranchPosition(Branch* _branch, side* _eBranchPos, int _numberOfBranches, int _seed);
        void resetBranches(Branch* _branch, side* _eBranchPos, int _numberOfBranches);
        
        side getBranchSide(){return mBranchSide;}
        void setBranchSide(side _side){mBranchSide = _side;}

        side getLethalBranch(Branch* _branches, side* _side, int _numberOfBranches);

        void cutLowestBranch(Branch* _branches, side* _side, int _numberOfBranches, bool& _isLogActive);


        
};

