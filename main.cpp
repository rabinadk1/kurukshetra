#include <SFML/Graphics.hpp>

#include <iostream>

#include "includes/Player.h"
#include "includes/Platform.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kurukshetra");

    sf::View gameView;
    sf::View minimapView;
    gameView.setCenter(sf::Vector2f(400.f, 300.f));
    gameView.setSize(sf::Vector2f(800.f, 600.f));


    minimapView.setSize(sf::Vector2f(200.f, 200.f));

    gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


    sf::Texture skyTexture;
    sf::Texture groundTexture;
    sf::Texture rockTexture;
    sf::Texture playerTexture;
    sf::Texture grassTexture;

    if(!skyTexture.loadFromFile("../Media/Textures/sereneBackground.png"))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }
    if(!grassTexture.loadFromFile("../Media/Textures/grass.png"))
    {
        std::cout << "Load Failed" << std::endl;
        system("pause");
    }
    if(!rockTexture.loadFromFile("../Media/Textures/rockPlatform.png"))
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
//    sky.setFillColor(sf::Color(102, 0, 0));

    Platform ground(&groundTexture, sf::Vector2f(1920, 80), sf::Vector2f(0, 520));

    sf::RectangleShape grass;
    grass.setPosition(sf::Vector2f(1200, 420));
    grass.setSize(sf::Vector2f(100, 100));
    grass.setTexture(&grassTexture);

    sf::RectangleShape rock;
    rock.setPosition(sf::Vector2f(300, 420));
    rock.setSize(sf::Vector2f(300, 50));
    rock.setTexture(&rockTexture);

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

        window.setView(gameView);

        player.Update(deltaTime, gameView);

        window.clear();

        window.draw(sky);
        window.draw(grass);
        window.draw(rock);
//        ground.Draw(window);
        player.Draw(window);
        window.display();

    }

    return 0;
}