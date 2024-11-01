#include "headers/preload.h"
#include "headers/GlobalEnums.h"



preload::preload(){


    textureBackground.loadFromFile("/Users/johnfry/TimberMac/timbermac/graphics/background.png");
    textureBee.loadFromFile(graphicsFilePath+"bee.png");
    textureTree.loadFromFile(graphicsFilePath+"tree.png");
    textureCloud.loadFromFile(graphicsFilePath+"cloud.png");
    textureBranch.loadFromFile(graphicsFilePath+"branch.png");
    texturePlayer.loadFromFile(graphicsFilePath+"player.png");
    //todo set these up with pointers later on
    
   

    
    Player playerCharacter = Player(preload::texturePlayer,0,0,true,0);



}

