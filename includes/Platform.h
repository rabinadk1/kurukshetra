//
// Created by safal on 14/2/19.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform {
public:
//    Platform(){}
//    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    void SetData(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }

private:
    sf::RectangleShape body;
};
