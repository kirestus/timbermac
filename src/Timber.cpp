#include <iostream>
#include <vector>
#include <string>
#include "headers/GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;


int main()
{

    Clock clockTime;

    srand((int)time(0));
    int number = (rand() % 100);

    std::string graphicsFilePath = "/Users/johnfry/TimberMac/timbermac/graphics/";// i hate having to do this

    int playerScore = 0;

    VideoMode vm(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber");

    Texture textureBackground;
    textureBackground.loadFromFile(graphicsFilePath+"background.png");

    Texture textureBee;
    textureBee.loadFromFile(graphicsFilePath+"bee.png");

    Texture textureTree;
    textureTree.loadFromFile(graphicsFilePath+"tree.png");

    Texture textureCloud;
    textureCloud.loadFromFile(graphicsFilePath+"cloud.png");

    GameObject backGround = GameObject(textureBackground, 0, 0, false);
    GameObject tree = GameObject(textureTree, 810,0, false);


    GameObject bee = GameObject(textureBee, 0, 0, true);
    bee.getSprite().scale(-1, 1);
    bee.updatePos(300, 100);
    bee.setSpeed(Vector2f(0.004, 0.00001));


    GameObject cloud = GameObject(textureCloud, 400, 90, true);
    cloud.setSpeed(Vector2f(0.0001, 0));
    cloud.getSprite().scale(1.4, 1.6);

    GameObject cloud2 = GameObject(textureCloud, 200, 200, true);
    Vector2f cloudSpeed2(0.0003f*number/50, 0.0f);
    cloud2.setSpeed(cloudSpeed2);




    bool isBeeActive = true;
    float beeSpeed = 0.3f;

    while (window.isOpen())
    {
        window.clear();// clear the screen before drawing the next frame
         sf::Event event;

        /*********************************************************
        Update the Scene
        *********************************************************/
        
        Time dt = clockTime.restart(); //deltaTime

        cloud2.move();
        cloud.move();
        bee.move();

        //bee.setPosition(beeXpos+=beeSpeed, bee.getPosition().y);

        /*********************************************************
        Draw The Scene
        *********************************************************/
        backGround.drawGO(window);
        cloud2.drawGO(window);
        cloud.drawGO(window);
        tree.drawGO(window);
        bee.drawGO(window);


        window.display();
        /*********************************************************
        Check For User Inputs
        *********************************************************/
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        // Track Time
        
        dt = clockTime.getElapsedTime();



    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
