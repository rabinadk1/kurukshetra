//
// Created by samip on 25/2/19.
//

#include <cmath>
#include "Enemy.h"
void Enemy::Update(float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window)
{
    static sf::Vector2f movement(0.f, 0.f);
    static sf::Vector2f bulletMovement(0.f, 0.f);
    static float localVelocity = velocity.y;
    const float g = 9.81f;
    bool isUp = body.getPosition().y <= baseHeight;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= velocity.x * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += velocity.x * deltaTime;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
//        movement.y += velocity.x * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        isJumping = true;

    sf::Vector2f mousePos, moveDirection;
    if (not isShooting and sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pixelMousePos = sf::Mouse::getPosition();
        mousePos = window.mapPixelToCoords(pixelMousePos);
        sf::Vector2f localBulletPos = bullet.getPosition();

        sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
        double distance = sqrt(double(displacement.x*displacement.x + displacement.y*displacement.y));

        moveDirection = sf::Vector2f(float(displacement.x/distance) , float(displacement.y/distance));
        isShooting = true;
    }

    if (isShooting)
    {
        if(bullet.getPosition() == mousePos)
        {
            isShooting = false;
            bullet.setPosition(1000.f, 1.4f * (600.f - 50.f));
        }
    }

    if (not isUp)
    {
        body.setPosition(body.getPosition().x, baseHeight);
        isJumping = false;
        localVelocity = velocity.y;
    }

    if(movement.x == 0)
        row = 0;
    else
    {
        row = 1;
        faceRight = movement.x > 0;
    }
    gameView.move(movement);
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    bullet.move(bulletMovement);

    if (not isShooting)
        bulletMovement = sf::Vector2f(0.f, 0.f);
    else
    {
        bulletMovement.x += moveDirection.x * velocity.x * deltaTime;
        bulletMovement.y += moveDirection.y * velocity.x * deltaTime;
    }

    if (not isJumping)
        movement = sf::Vector2f(0.f,0.f);
    else
    {
        movement.y -= localVelocity * deltaTime;
        localVelocity -= g;
    }
}