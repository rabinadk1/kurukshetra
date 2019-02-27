//
// Created by samip on 13/2/19.
//

#include <iostream>
#include "MainMenu.h"
#include "Game.h"
void MainMenu::render(){
    mWindow2.clear();
    for(int i=0;i<3;i++) {
        menu[i].setFillColor(i==selectedItem? sf::Color::Red : sf::Color::White);
        mWindow2.draw(menu[i]);
    }
    mWindow2.display();
}
MainMenu::MainMenu(unsigned int width, unsigned int height)
	:fonts(Fonts::fontNumber),
    selectedItem(0),
	isPressedUp(false),
	isPressedDown(false),
	isPressedReturn(false),
	mWindow2(sf::VideoMode(width, height), "Kurukshetra"),
	width(width),
    height(height)
{
    fonts.load(Fonts::menuFont, "../Media/Fonts/DejaVuSans.ttf");
    for (int i=0; i<3; i++)
        menu[i].setFont(fonts.get(Fonts::menuFont));
    menu[0].setString("Play");
    menu[1].setString("About");
    menu[2].setString("Exit");
    for (int i=0; i<3; i++)
        menu[i].setPosition(width/2.f,height/4.f*i);
}
void MainMenu::moveUp(const bool goUp = true) {
    if (goUp and selectedItem != 0)
        selectedItem--;
    else if(not goUp and selectedItem!=2)
        selectedItem++;
}
void MainMenu::handlePlayerInput(sf::Keyboard::Key &key, bool isPressed) {
    switch (key){
        case sf::Keyboard::Up:
            isPressedUp=isPressed;
            break;
        case sf::Keyboard::Down:
            isPressedDown=isPressed;
            break;
        case sf::Keyboard::Return:
            isPressedReturn=isPressed;
            break;
    }
    update();
}

void MainMenu::update() {
    if(isPressedUp)
        moveUp();
    if(isPressedDown)
        moveUp(false);
    if(isPressedReturn)
        onPressEnter();
}

void MainMenu::onPressEnter(){
    switch (selectedItem)
    {
        case 2:
            std::cout<<"Program exited successfully!"<<std::endl;
            exit(0);
        case 0:
            mWindow2.close();
            Game game(width, height);
            game.run();
            break;
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
                break;
            case sf::Event::Closed:
                mWindow2.close();
                break;
        }
    }
}

