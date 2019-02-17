//
// Created by maverick on 12/2/19.
//

#pragma once

#include "TextureHolder.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
//    void handlePlayerInput(sf::Keyboard::Key& key, bool isPressed);

private:
    sf::RenderWindow mWindow;
    TextureHolder textures;
    Player player;
    sf::RectangleShape sky;
    sf::RectangleShape ground;
    sf::RectangleShape grass;
    Animation animation;
    sf::Clock clock;
};
