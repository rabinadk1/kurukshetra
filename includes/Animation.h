//
// Created by safal on 13/2/19.
//

#ifndef TEST_ANIMATION_H
#define TEST_ANIMATION_H


#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};


#endif //TEST_ANIMATION_H
