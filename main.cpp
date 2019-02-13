#include <SFML/Graphics.hpp>

#include <iostream>

#include "includes/Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kurukshetra");

    sf::Texture skyTexture;
    sf::Texture groundTexture;
    sf::Texture playerTexture;
    sf::Texture grassTexture;

    if(!skyTexture.loadFromFile("../Media/Textures/redSky.jpg", sf::IntRect(100, 100, 300, 300)))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }
    if(!grassTexture.loadFromFile("../Media/Textures/grass.png"))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }
    skyTexture.setRepeated(true);

    if(!groundTexture.loadFromFile("../Media/Textures/ground.jpg"))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }
    groundTexture.setRepeated(true);

    if(!playerTexture.loadFromFile("../Media/Textures/fox.png"))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }

    Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 150.0f);

    sf::RectangleShape sky;
    sky.setPosition(sf::Vector2f(0, 0));
    sky.setSize(sf::Vector2f(1920, 600));
    sky.setTexture(&skyTexture);
    sky.setFillColor(sf::Color(102, 0, 0));


    sf::RectangleShape ground;
    ground.setPosition(sf::Vector2f(0, 520));
    ground.setSize(sf::Vector2f(1920, 80));
    ground.setFillColor(sf::Color(255, 255, 255, 255)); //128 is half transparency
    ground.setTexture(&groundTexture);
    ground.setFillColor(sf::Color(255, 174, 0, 128));

    sf::RectangleShape grass;
    grass.setPosition(sf::Vector2f(1200, 420));
    grass.setSize(sf::Vector2f(100, 100));
    grass.setTexture(&grassTexture);

    Animation animation(&playerTexture, sf::Vector2u(3,9), 0.3f);

    float deltaTime = 0.f;
    sf::Clock clock;
    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event = {};
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        player.Update(deltaTime);


        window.clear();

        window.draw(sky);
        window.draw(grass);
        window.draw(ground);
        player.Draw(window);
        window.display();

    }

    return 0;
}