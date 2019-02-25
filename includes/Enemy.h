//
// Created by samip on 25/2/19.
//

#ifndef KURUKSHETRA_ENEMY_H
#define KURUKSHETRA_ENEMY_H


#include <Player.h>

class Enemy: public Player {
public:
    void Update(float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window);
};
#endif //KURUKSHETRA_ENEMY_H
