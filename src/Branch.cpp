#include "headers/Branch.h"


Branch::Branch():GameObject(){
    //int numberOfBranches = 6;
    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  

}

Branch::Branch(sf::Texture& _texture, float posX, float posY, bool _shouldCenterSprite, int _id) 
: GameObject(_texture, posX, posY, _shouldCenterSprite=true, sf::Vector2f(1.0f,1.0f), 0.0f){

    textureBranch.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/branch.png");  

}

void Branch::createBranches(int _itter, side _branchPositions){
    //update branches sprites

    float height = _itter*150-200;


    if (_branchPositions == side::LEFT)
    {
        this->updatePos(900,height);
        //branches[i].setFlopped();
    }

    else if (_branchPositions == side::RIGHT)
    {
        this->updatePos(350,height);
        this->flopGO();
    }

    else
    {
        this->updatePos(3000,height);
    }
    
}

void Branch::updateBranchPosition(int _seed, side* _branchPositions)//this is still busted need to fix next time
{
    for (int j = mNumberOfBranches-1; j > 0 ; j--)
    {
        _branchPositions[j] = _branchPositions[j-1];
    }
    
    
    srand((int)time(0)+_seed);
    int r = (rand()%5);

    std::cout<<r;

    switch(r) {
        case 0:
        _branchPositions[0] = side::LEFT;
        break;

        case 1:
        _branchPositions[0] = side::RIGHT;
        break;

        default:
        _branchPositions[0] = side::NONE;
        break;

    }
    std::cout<<_branchPositions;
}

void Branch::renderBranches(sf::RenderWindow& _window, Branch* _branches){
    for (int i = 0; i < mNumberOfBranches; i++)
    {
        _branches[i].drawGO(_window);
    }
}