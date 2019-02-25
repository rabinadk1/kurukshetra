//
// Created by safal on 13/2/19.
//

#pragma once

#include "Animation.h"
#include "Collider.h"
#include "Camera.h"

class Player {
public:
    void SetData(sf::Texture* playerTexture, sf::Texture* bulletTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
    void Update(float deltaTime, Camera& gameView, float &baseHeight, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }
    void SetPosition(sf::Vector2f position);

    sf::Vector2f GetPosition();

private:
    sf::RectangleShape body, bullet;
    Animation animation;
    unsigned row;
    bool faceRight, isJumping, isShooting;
    sf::Vector2f velocity;
};
