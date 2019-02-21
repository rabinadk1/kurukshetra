//
// Created by safal on 13/2/19.
//

#include <iostream>
#include "Player.h"

void Player::SetData(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
    animation.SetData(texture, imageCount, switchTime);
    this -> speed = speed;
    row = 0;
    faceRight = true;
    isJumping = false;
	const sf::Vector2f playerSize = sf::Vector2f(100.0f, 150.0f);
    body.setSize(playerSize);
    body.setPosition(position);
    body.setTexture(texture);
    body.setOrigin(playerSize);
    velocity = sf::Vector2f(speed, 0.5f*speed);
}

void Player::Update(float deltaTime, sf::View &gameView, float &baseHeight)
{
    static sf::Vector2f movement(0.f, 0.f);
    const float g = 9.81f;
    bool isUp = body.getPosition().y <= baseHeight;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
        movement.y += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and not isJumping)
    {
//        movement.y -= speed * deltaTime;
        isJumping = true;
    }

    if (not isUp)
    {
        body.setPosition(body.getPosition().x, baseHeight);
        isJumping = false;
        velocity.y = .5f*speed;
    }
    if(movement.x == 0)
    {
        row = 0;
    }
    else
    {
        row = 1;
        faceRight = movement.x > 0;
    }
	gameView.move(movement);
	animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);

    if (not isJumping)
        movement = sf::Vector2f(0.f,0.f);
    else
    {
            movement.y -= velocity.y * deltaTime;
            velocity.y -= g;
    }
}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(body);
}

void Player::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}
