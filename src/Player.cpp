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

void Player::Update(float deltaTime, sf::View &gameView) {
    sf::Vector2f movement(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movement.x -= speed * deltaTime;
        gameView.move(movement.x, 0.f);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movement.x += speed * deltaTime;
        gameView.move(movement.x, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed * deltaTime;
        gameView.move(0.f, movement.y);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movement.y -= speed * deltaTime;
        gameView.move(0.f, movement.y);
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
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

void Player::Draw(sf::RenderWindow &window) {
    window.draw(body);
}

void Player::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}
