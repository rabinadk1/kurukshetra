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
    void SetData(sf::Vector2f size, sf::Vector2f position);
    void SetTexture(sf::Texture* texture);
    void SetSize(sf::Vector2f size);
    void SetPosition(sf::Vector2f position);
    void SetTextureRect(sf::IntRect textureRect);

    sf::Vector2f GetSize(){ return body.getSize();}
    Platform SetWalls(sf::Texture texture, sf::Vector2f size, sf::Vector2f position);
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }

private:
    sf::RectangleShape body;
};
