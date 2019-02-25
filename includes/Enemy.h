//
// Created by samip on 25/2/19.
//

#pragma once


#include <Player.h>

class Enemy: public Player {
public:
    void Update(sf::Texture* bulletTexture, float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window);
};
