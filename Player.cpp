//
// Created by safal on 13/2/19.
//

#include "Player.h"


void Player::SetData(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed) {
    animation.SetData(texture, imageCount, switchTime);
    this -> speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setPosition(200.f, 372.f);
    body.setTexture(texture);
}
Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed)
{
    SetData(texture, imageCount, switchTime, speed);
}

void Player::Update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;

    if(movement.x == 0)
    {
        row = 0;
    }
    else
    {
        row = 1;
        if(movement.x > 0)
            faceRight = true;
        else
            faceRight = false;
    }
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(body);
}
