//
// Created by maverick on 12/2/19.
//

#pragma once

#include "../src/ResourceHolder.cpp"
#include "Player.h"
#include "Platform.h"
#include "../Server/src/GameServer.h"
#include "../Server/src/Enemy.h"

namespace Textures
{
	enum ID {skyTexture, groundTexture, rockTexture, playerTexture, grassTexture, bulletTexture, textureNumber};
}

class Game {
public:
    Game(unsigned viewWidth, unsigned viewHeight);
    void run();

private:
    void processEvents();
    void update();
    void render();

    void ResizedWindow(sf::RenderWindow& window, sf::View& view);

private:
    sf::RenderWindow window;
    ResourceHolder <sf::Texture, Textures::ID> textures;
    Player player;
    GameServer server;
    Enemy enemy;
    sf::RectangleShape sky, grass, rock;
    Animation animation;
    sf::Clock clock;
    sf::View gameView, minimapView;
    Platform ground;
    float viewWidth;
    float viewHeight, baseHeight;
};
