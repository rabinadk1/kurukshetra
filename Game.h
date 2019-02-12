//
// Created by maverick on 12/2/19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Controller/remainTime.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
    sf::RenderWindow mWindow;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
    remainTime R;
    sf::Font font;
    sf::Text time;
};
