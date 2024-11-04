#include "headers/Branch.h"

Branch::Branch():GameObject(){
    //create an empty branch 

}

Branch::Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id) 
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){
    
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

    float height = _index*120.0-120.0;
    //std::cout<<_branchPositions;


    if (_eBranchPos[_index] == side::RIGHT)
    {
        this->updatePos(900,height);
            if (getSprite().getScale().x < 0 )
            {
                getSprite().setScale(sf::Vector2f(1,1));
            }
    }

    else if (_eBranchPos[_index] == side::LEFT)
    {
        this->updatePos(350,height);
            if (getSprite().getScale().x > 0 )
            {
                getSprite().setScale(sf::Vector2f(-1,1));
            }
    }

    else
    {
        this->updatePos(3000,height);
    }

    
}

void Branch::updateBranchPosition(Branch* _branches,side* _eBranchPos,int _numberOfBranches,int _seed)
//this runs each time a branch is created or cut down,
{
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

side Branch::getLethalBranch(Branch* _branches, side* _side, int _numberOfBranches)
{
    return _side[_numberOfBranches-2];
}

void Branch::cutLowestBranch(Branch* _branches, side* _side, int _numberOfBranches, bool& _isLogActive)
{
    _side[_numberOfBranches-2] = side::NONE;
    _isLogActive = true;
}
void Branch::renderBranches(sf::RenderWindow& _window, Branch* _branches, int _numberOfBranches){
    //render each branch
    for (int i = 0; i < _numberOfBranches; i++)
    {
        _branches[i].drawGO(_window);
    }
}