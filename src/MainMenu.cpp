//
// Created by samip on 13/2/19.
//

#include <iostream>
#include "MainMenu.h"
#include "Game.h"
void MainMenu::render(){
    mWindow2.clear();
    for(int i=0;i<4;i++) {
        menu[i].setFillColor(i==selectedItem? sf::Color::Red : sf::Color::White);
        mWindow2.draw(menu[i]);
    }
    mWindow2.display();
}
MainMenu::MainMenu(unsigned int width, unsigned int height)
	:font(1),
    selectedItem(3),
	isPressedUp(false),
	isPressedDown(false),
	isPressedReturn(false),
	mWindow2(sf::VideoMode(width, height), "Kurukshetra")
{
    font.load(Fonts::menuFont, "../Media/Fonts/DejaVuSans.ttf");
    for (int i=0; i<4; i++)
        menu[i].setFont(font.get(Fonts::menuFont));
    menu[0].setString("Play Single");
    menu[0].setPosition(width/2.f,height/4.f*0);
    menu[1].setString("Play with Friend");
    menu[1].setPosition(width/2.f,height/4.f*1);
    menu[2].setString("Options");
    menu[2].setPosition(width/2.f,height/4.f*2);
    menu[3].setString("Exit");
    menu[3].setPosition(width/2.f,height/4.f*3);
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
    if(isPressedUp) {
       moveUp();
    }
    if(isPressedDown)
       moveDown();
    if(isPressedReturn)
        onPressEnter();
}

void MainMenu::onPressEnter(){
    switch (selectedItem)
    {
        case 3:
            std::cout<<"Program exited successfully!"<<std::endl;
            exit(0);
        case 0:
            mWindow2.close();
            Game game(800.f, 600.f);
            game.run();
            break;
    }
    if(selectedItem == 0)
    {

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
void MainMenu::moveDown() {
    if(selectedItem!=3)
    {
        selectedItem++;
    }
}
