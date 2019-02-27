//
// Created by samip on 27/2/19.
//

#include "IpEnter.h"
void IpEnter::render(){
    mWindow2.clear();
    mWindow2.draw(enter);
    mWindow2.draw(playerText);
    mWindow2.display();
}
IpEnter::IpEnter(unsigned int width, unsigned int height)
        :fonts(Fonts::fontNumber),
         isPressedReturn(false),
         mWindow2(sf::VideoMode(width, height), "Kurukshetra"),
         width(width),height(height)
{
    fonts.load(Fonts::menuFont, "../Media/Fonts/DejaVuSans.ttf");
    enter.setString("Please Enter IP:");
    enter.setPosition(0,0);
    enter.setFont(fonts.get(Fonts::menuFont));
    playerText.setPosition(0,enter.getCharacterSize());
    playerText.setFont(fonts.get(Fonts::menuFont));
}
void IpEnter::handlePlayerInput(sf::Keyboard::Key &key, bool isPressed) {
        switch (key){
            case sf::Keyboard::Return:
                onPressEnter();
                break;
            default:
                break;
        }
    }
void IpEnter::onPressEnter()
{
    if(!playerInput.isEmpty())
    {
        mWindow2.close();
        Game game(width, height,playerInput);
        game.run();
    }
    else
        enter.setString("You must Enter the IP:");
}
void IpEnter::run() {
    while (mWindow2.isOpen())
    {
        processEvents();
        render();
    }
}
void IpEnter::processEvents() {
    sf::Event event = {};
    while (mWindow2.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::TextEntered:
                if((event.text.unicode>=48 && event.text.unicode<=57)||(event.text.unicode==46))
                {
                    playerInput+=event.text.unicode;
                    playerText.setString(playerInput);
                }else if(event.text.unicode==8 && !playerInput.isEmpty())
                {
                    playerInput.erase(playerInput.getSize()-1,1);
                    playerText.setString(playerInput);
                }
            mWindow2.draw(playerText);
                break;
            case sf::Event::Closed:
                mWindow2.close();
                break;
        }
    }
}