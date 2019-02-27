//
// Created by samip on 27/2/19.
//

#ifndef KURUKSHETRA_GLOBAL_H
#define KURUKSHETRA_GLOBAL_H

#include <SFML/System/Vector2.hpp>

struct clientInfo
{
    sf::Vector2f bodyPosition;
    sf::Vector2f bodyMovement;
    sf::Vector2f bullet;
    bool isshooting;
};
#endif //KURUKSHETRA_GLOBAL_H
