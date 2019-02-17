//
// Created by safal on 13/2/19.
//

#pragma once

#include "Animation.h"
class Player {
public:
    Player(){}
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player(){}

    void SetData(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);


private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
};

