//
// Created by safal on 13/2/19.
//

#pragma once

#include "Animation.h"
#include "Collider.h"

class Player {
public:
    void SetData(sf::Texture* playerTexture, sf::Texture* bulletTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
    void Update(float deltaTime, sf::View& gameView, float &baseHeight, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }
    void SetPosition(sf::Vector2f position);
    void HitCheck(sf::RectangleShape& bullet);
    bool isDead(){ return health<=0;}
    bool isUp(sf::RectangleShape& shape, float& baseHeight);
private:
    sf::RectangleShape body, bullet;
    Animation animation;
    unsigned row;
    bool faceRight, isJumping, isShooting, canFly;
    sf::Vector2f velocity, bulletVelocity;
public:
	int health, mana;
};
