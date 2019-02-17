//
// Created by safal on 14/2/19.
//

#include "Platform.h"


void Platform::SetData(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
//    body.setOrigin(size);
    body.setTexture(texture);
    body.setPosition(position);
}

//Platform::Platform(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
//    SetData(texture, size, position);
//}

void Platform::Draw(sf::RenderWindow &window) {
    window.draw(body);
}

