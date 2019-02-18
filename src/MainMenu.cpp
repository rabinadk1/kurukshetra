//
// Created by samip on 13/2/19.
//

#include <iostream>
#include "MainMenu.h"
#include "Game.h"
void MainMenu::render(){
    mWindow2.clear();
    for(int i=0;i<4;i++) {
        menu[i].setFillColor(i==selectedItem?sf::Color::Red:sf::Color::White);
        mWindow2.draw(menu[i]);
    }
    mWindow2.display();
}
MainMenu::MainMenu(float width, float height):selectedItem(3),isPressedUp(false),isPressedDown(false),isPressedReturn(false),mWindow2(sf::VideoMode(800, 600), "Kurukshetra") {
    if(!font.loadFromFile("../DejaVuSans.ttf"))
    {
        std::cerr<<"Error loading font";
    }
    menu[0].setFont(font);
    menu[0].setString("Play Single");
    menu[0].setPosition(width/2,height/4*0);
    menu[1].setFont(font);
    menu[1].setString("Play with Friend");
    menu[1].setPosition(width/2,height/4*1);
    menu[2].setFont(font);
    menu[2].setString("Options");
    menu[2].setPosition(width/2,height/4*2);
    menu[3].setFont(font);
    menu[3].setString("Exit");
    menu[3].setPosition(width/2,height/4*3);
}
void MainMenu::moveUp() {
    if(selectedItem!=0){
        selectedItem--;
    }
}
void MainMenu::handlePlayerInput(sf::Keyboard::Key &key, bool isPressed) {
    switch (key){
        case sf::Keyboard::Up:
            isPressedUp=isPressed;
            update();
            break;
        case sf::Keyboard::Down:
            isPressedDown=isPressed;
            update();
            break;
        case sf::Keyboard::Return:
            isPressedReturn=isPressed;
            update();
            break;
    }
}

void MainMenu::update() {
    if(isPressedUp) {
       moveUp();
    }
    if(isPressedDown)
       moveDown();
    if(isPressedReturn)
        onPressEnter();
}

void MainMenu::onPressEnter(){
    if(selectedItem == 0)
    {
        mWindow2.close();
        Game game;
        game.run();
    }
}
void MainMenu::run() {
    while (mWindow2.isOpen())
    {
        processEvents();
        render();
    }
}

void MainMenu::processEvents() {
    sf::Event event = {};
    while (mWindow2.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                std::cout<<"Released";
                break;
            case sf::Event::Closed:
                mWindow2.close();
                break;
        }
    }
}
void MainMenu::moveDown() {
    if(selectedItem!=3)
    {
        selectedItem++;
    }
}
