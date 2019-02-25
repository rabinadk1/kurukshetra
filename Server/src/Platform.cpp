//
// Created by safal on 14/2/19.
//

#include <Platform.h>

#include "Platform.h"


void Platform::SetData(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
//    body.setOrigin(size);
    body.setTexture(texture);
    body.setPosition(position);
}


void Platform::Draw(sf::RenderWindow &window) {
    window.draw(body);
}

void Platform::SetTexture(sf::Texture *texture) {
    body.setTexture(texture);
}

void Platform::SetSize(sf::Vector2f size) {
    body.setSize(size);
}

void Platform::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}

std::vector<Platform> Platform::SetWalls(sf::Texture &texture,sf::RenderWindow &window){
    std::vector<Platform> walls;
    Platform wall1;
    wall1.SetData(&texture, sf::Vector2f(500, 50), sf::Vector2f(1200, 1700));
    walls.push_back(wall1);
    wall1.SetData(sf::Vector2f(300, 100), sf::Vector2f(500, 1800));
    walls.push_back(wall1);
    wall1.SetData(sf::Vector2f(100, 150), sf::Vector2f(1400, 1750));
    walls.push_back(wall1);

    return walls;
}

void Platform::SetData(sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setPosition(position);
}

void Platform::SetTextureRect(sf::IntRect textureRect) {
    body.setTextureRect(textureRect);
}

