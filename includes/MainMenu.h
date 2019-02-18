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
    enum ID {menuFont};
}

class MainMenu{
public:
    MainMenu(unsigned int width, unsigned int height);
    void run();

private:
    void moveUp();
    void moveDown();
    void render();
    void handlePlayerInput(sf::Keyboard::Key &key, bool isPressed);
    void update();
    void processEvents();
    void onPressEnter();
    //  void draw(sf::RenderWindow &window);
private:
    sf::Text menu[4];
//    sf::Font font;
    ResourceHolder <sf::Font, Fonts::ID> font;
    int selectedItem;
    bool isPressedUp, isPressedDown, isPressedReturn;
    sf::RenderWindow mWindow2;
};
