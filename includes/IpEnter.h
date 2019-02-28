//
// Created by samip on 27/2/19.
//

#ifndef KURUKSHETRA_IPENTER_H
#define KURUKSHETRA_IPENTER_H


#include <SFML/Graphics/Text.hpp>
#include <MainMenu.h>

class IpEnter {
public:
    IpEnter(unsigned int width, unsigned int height);
    void render();
    void run();
    void handlePlayerInput(sf::Keyboard::Key &key, bool isPressed);
    void update();
    void processEvents();
    void onPressEnter();
private:
    sf::Text menu[3];
    ResourceHolder <sf::Font, Fonts::ID> fonts;
    sf::RenderWindow mWindow2;
    sf::RectangleShape inputBox;
    sf::String playerInput;
    sf::Text playerText,enter;
    bool isPressedReturn;
    unsigned width, height;
};


#endif //KURUKSHETRA_IPENTER_H
