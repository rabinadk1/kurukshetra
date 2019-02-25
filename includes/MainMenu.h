//
// Created by samip on 13/2/19.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"

namespace Fonts
{
    enum ID {menuFont, fontNumber};
}

class MainMenu{
public:
    MainMenu(unsigned int width, unsigned int height);
    void run();

private:
    void moveUp(bool goUp);
//    void moveDown();
    void render();
    void handlePlayerInput(sf::Keyboard::Key &key, bool isPressed);
    void update();
    void processEvents();
    void onPressEnter();
private:
    sf::Text menu[4];
    ResourceHolder <sf::Font, Fonts::ID> fonts;
    int selectedItem;
    bool isPressedUp, isPressedDown, isPressedReturn;
    sf::RenderWindow mWindow2;
    unsigned width, height;
};
