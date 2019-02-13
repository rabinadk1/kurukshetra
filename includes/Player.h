//
// Created by safal on 13/2/19.
//

#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
class Player {
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);


private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
};


#endif //TEST_PLAYER_H
