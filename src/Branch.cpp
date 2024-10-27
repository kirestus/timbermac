#include "headers/Branch.h"


Branch::Branch():GameObject(){
    //int numberOfBranches = 6;
    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  
    side branchPositions[mNumberOfBranches];

}

Branch::Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id) 
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){
    
    side branchPositions[mNumberOfBranches];

    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  

}

void Branch::createBranches(int _itter){
    //update branches sprites

    float height = _itter*150-200;


    if (this->branchPositions[_itter] == side::LEFT)
    {
        this->updatePos(900,height);
        //branches[i].setFlopped();
    }

    else if (this->branchPositions[_itter] == side::RIGHT)
    {
        this->updatePos(350,height);
        this->flopGO();
    }

    else
    {
        this->updatePos(3000,height);
    }
    
}

void Branch::updateBranchPosition(int _seed , int _numberOfBranches)//this is still busted need to fix next time
{
    for (int j = _numberOfBranches-1; j > 0; j--)
    {
        this->branchPositions[j] = this->branchPositions[j-1];
    }
    srand((int)time(0)+_seed);
    int r = (rand()%5);

    switch(r) {
        case 0:
        this->branchPositions[0] = side::LEFT;
        break;

        case 1:
        this->branchPositions[0] = side::RIGHT;
        break;

        default:
        this->branchPositions[0] = side::NONE;
        break;

    }
}

void Branch::renderBranches(sf::RenderWindow& _window, Branch* _branches){
    for (int i = 0; i < mNumberOfBranches; i++)
    {
        std::cout<< _branches[i].getPos().x <<" " << _branches[i].getPos().y<< std::endl;
        _branches[i].drawGO(_window);
    }
}