//
// Created by safal on 13/2/19.
//

#include <iostream>
#include <Player.h>
#include <cmath>

#include "Player.h"

void Player::SetData(sf::Texture *playerTexture, sf::Texture* bulletTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
    animation.SetData(playerTexture, imageCount, switchTime);
    row = 0;
    faceRight = true;
    isJumping = isShooting = false;

	const sf::Vector2f playerSize = sf::Vector2f(100.0f, 150.0f);
    body.setSize(playerSize);
    body.setPosition(position);
    body.setTexture(playerTexture);
    body.setOrigin(playerSize);
//    body.setOrigin(playerSize.x/2, playerSize.y/2);

    const sf::Vector2f bulletSize = sf::Vector2f(20.f, 12.4f);
    bullet.setSize(bulletSize);
    bullet.setPosition(position.x+50, position.y-50);
    bullet.setTexture(bulletTexture);
//    bullet.setOrigin(bulletSize);
    bullet.setOrigin(bulletSize.x/2, bulletSize.y/2);

    velocity = sf::Vector2f(speed, 0.8f*speed);
}

void Player::Update(float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window)
{
    static sf::Vector2f movement(0.f, 0.f);
    static sf::Vector2f bulletMovement(0.f, 0.f);
    static float localVelocity = velocity.y;
    const float g = 9.81f;
    bool isUp = body.getPosition().y <= baseHeight;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movement.x -= velocity.x * deltaTime;
        gameView.Move(sf::Vector2f(movement.x, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movement.x += velocity.x * deltaTime;
        gameView.Move(sf::Vector2f(movement.x, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        isJumping = true;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and not isJumping)
//    {
////        movement.y -= speed * deltaTime;
//        isJumping = true;
//        gameView.move(0, movement.y);
//    }

//        movement.x -= velocity.x * deltaTime;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        movement.x += velocity.x * deltaTime;
////    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
////        movement.y += velocity.x * deltaTime;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        isJumping = true;


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
//	gameView.move(movement);
	animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    bullet.move(bulletMovement);
//    gameView.Update(body.getPosition(), window);

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

void Player::Draw(sf::RenderWindow &window) {
    window.draw(body);
    window.draw(bullet);
}

void Player::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}

sf::Vector2f Player::GetPosition() {
    return body.getPosition();
}
