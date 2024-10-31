#include "headers/Branch.h"

Branch::Branch():GameObject(){
    //create an empty branch
    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  

}

Branch::Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id) 
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){
    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  
    
}

void Branch::resetBranches(Branch* _branch, side* _eBranchPos, int _numberOfBranches)
{
    for(int i=0; _numberOfBranches>i; i++)
    {
        _eBranchPos[i] = side::NONE;
    }

}

void Branch::moveBranch(Branch* _branch, side* _eBranchPos, int _index){
//move the branches, this runs on update 

    float height = _index*70+50;
    //std::cout<<_branchPositions;


    if (_eBranchPos[_index] == side::LEFT)
    {
        this->updatePos(900,height);
        //branches[i].setFlopped();
    }

    else if (_eBranchPos[_index] == side::RIGHT)
    {
        this->updatePos(350,height);
        if(this->getIsFlopped() == false)
        {
            this->flopGO();
        }
        
    }

    else
    {
        this->updatePos(3000,height);
    }

    
}

void Branch::updateBranchPosition(int _seed,int _numberOfBranches, side* _eBranchPos)
//this runs each time a branch is created or cut down,
{
        //side branchPos = branchPos
        for (int j = _numberOfBranches-1; j>0; j--)
        {
            _eBranchPos[j] = _eBranchPos[j-1];
        }

        srand((int)time(0)+_seed);
        int r = (rand()%5);
        
        switch(r) {
            case 0:
            _eBranchPos[0] =  side::LEFT;
            break;

            case 1:
            _eBranchPos[0]  = side::RIGHT;
            break;

            default:
            _eBranchPos[0] = side::NONE;
            break;

        }

}

void Branch::renderBranches(sf::RenderWindow& _window, Branch* _branches, int _numberOfBranches){
    //render each branch
    for (int i = 0; i < _numberOfBranches; i++)
    {
        _branches[i].drawGO(_window);
    }
}