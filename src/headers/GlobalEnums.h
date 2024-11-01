#pragma once
#include <SFML/Graphics.hpp>


namespace constants
{
    const int numberOfBranches = 6;
    const sf::Vector2f resolution(1280,720);
    const sf::Vector2f screenCenter(resolution.x/2,resolution.y/2);

} // namespace constants

enum class side{LEFT,RIGHT,NONE};

enum class eGO{TREE,AXE,BEE,BACKGROUND,LOG};

enum class eTextureList{
BACKGROUND,CLOUD,PLAYER,AXE,BEE,BRANCH,TREE,LOG
};

enum class eSFX{
DEATH,CHOP,PAUSE
};