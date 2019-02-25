//
// Created by samip on 25/2/19.
//

#include <cmath>
#include <iostream>
#include "Enemy.h"
void Enemy::Update(sf::Texture* bulletTexture, float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window)
{
    static sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f bulletMovement(0.f, 0.f);
    static float localVelocity = velocity.y;
    const float g = 9.81f;
    if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= velocity.x * deltaTime;
    if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += velocity.x * deltaTime;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
//        movement.y += velocity.x * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        isJumping = true;

    static sf::Vector2f mousePos;
    if (not isShooting and sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);

        sf::IntRect viewport = window.getViewport(gameView);
        if (viewport.contains(pixelMousePos))
        {
            mousePos = window.mapPixelToCoords(pixelMousePos);
            std::cout<<mousePos.y<<" "<<body.getPosition().y<<std::endl;
            if (mousePos.y<=baseHeight)
            {
                sf::Vector2f localBulletPos = body.getPosition();

                sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
                double distance = sqrt(double(displacement.x * displacement.x + displacement.y * displacement.y));

                moveDirection = sf::Vector2f(float(displacement.x / distance), float(displacement.y / distance));

                bulletVelocity = sf::Vector2f(4*velocity.x * moveDirection.x, 4*velocity.y * moveDirection.y);
                isShooting = true;
            }
        }
    }

//		if (isShooting and not isUp(bullet, baseHeight))
////	{
////		sf::Vector2f bulletPos = bullet.getPosition();
////
////		bool checkX, checkY;
////		if (moveDirection.x<0.f)
////			checkX = bulletPos.x<=mousePos.x;
////		else
////			checkX = bulletPos.x >= mousePos.x;
////
////		if (moveDirection.y<0.f)
////			checkY = bulletPos.y<=mousePos.y;
////		else
////			checkY = bulletPos.y >= mousePos.y;
//
////		if(checkX and checkY and not isUp(bullet, baseHeight))
//		{
//			isShooting = false;
//			bullet.setPosition(1000.f, 1.4f * (600.f - 50.f));
//			bulletVelocity.y = 0;
//		}
//		else if (isShooting)
//		{
//			bulletMovement.x += bulletVelocity.x * deltaTime;
//			bulletMovement.y += bulletVelocity.y * deltaTime;
//			bulletVelocity.y += g;
//		}
//	}
    if (isShooting)
    {
        Bullet newBullet(bulletTexture, sf::Vector2f(20.f, 12.4f), body.getPosition(), bulletVelocity);
        bullets.push_back(newBullet);
        isShooting = false;
    }

    if (not isUp(body, baseHeight))
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

    if (isJumping)
    {
        movement.y = -localVelocity * deltaTime;
        localVelocity -= g;
    }
    else
        movement = sf::Vector2f(0.f,0.f);
}