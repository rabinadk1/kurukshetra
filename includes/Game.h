//
// Created by maverick on 12/2/19.
//

#pragma once

#include "TextureHolder.h"
#include "Player.h"
#include "Platform.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
    TextureHolder textures;
    Player player;
    sf::RectangleShape sky;
    sf::RectangleShape grass;
    sf::RectangleShape rock;
    Animation animation;
    sf::Clock clock;
    sf::View gameView;
    sf::View minimapView;
    Platform ground;
};
