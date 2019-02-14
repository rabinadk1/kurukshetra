//
// Created by safal on 14/2/19.
//

#ifndef KURUKSHETRA_PLATFORM_H
#define KURUKSHETRA_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform {
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }

private:
    sf::RectangleShape body;
};


#endif //KURUKSHETRA_PLATFORM_H
