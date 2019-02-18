//
// Created by samip on 13/2/19.
//

#ifndef KURUKSHETRA_MAINMENU_H
#define KURUKSHETRA_MAINMENU_H


#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"

class MainMenu{
public:
    MainMenu(float width,float height);
    void moveUp();
    void moveDown();
    void render();
    void handlePlayerInput(sf::Keyboard::Key &key, bool isPressed);
    void update();
    void processEvents();
    void run();
    void onPressEnter();

    ~MainMenu(){};
    //  void draw(sf::RenderWindow &window);
private:
    sf::Text menu[4];
    sf::Font font;
    int selectedItem;
    bool isPressedUp;
    bool isPressedDown;
    bool isPressedReturn;
    sf::RenderWindow mWindow2;
};


#endif //KURUKSHETRA_MAINMENU_H
