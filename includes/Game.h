//
// Created by maverick on 12/2/19.
//

#pragma once

#include "../src/ResourceHolder.cpp"
#include "Player.h"
#include "Platform.h"
#include <Camera.h>
#include <vector>
namespace Textures
{
	enum ID {skyTexture, groundTexture, rockTexture, playerTexture, grassTexture, bulletTexture, textureNumber, wallTexture, barrelTexture};
}

class Game {
public:
    Game(unsigned viewWidth, unsigned viewHeight);
    void run();

private:
    void processEvents();
    void update();
    void render();

    void ResizedWindow(sf::RenderWindow& window, Camera& view);

private:
    sf::RenderWindow window;
    ResourceHolder <sf::Texture, Textures::ID> textures;
    Player player;
    sf::RectangleShape sky, grass, rock;
    Animation animation;
    sf::Clock clock;
    Camera gameView;
    sf::View minimapView;
    std::vector<Platform> walls;
    Platform wall, barrel, ground;
    std::vector<sf::Vector2f> wallsPosition;
    float viewWidth;
    float viewHeight, baseHeight;
};
