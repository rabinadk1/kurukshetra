//
// Created by safal on 13/2/19.
//

#include <iostream>
#include <Player.h>
#include <cmath>

#include "Player.h"

void Player::SetData(sf::Texture *playerTexture, sf::Texture* bulletTexture, sf::Vector2u imageCount, float switchTime, float speed,
                     float baseHeight) {
    animation.SetData(playerTexture, imageCount, switchTime);
    row = 0;
    faceRight = true;
    isJumping = isShooting = false;
    m_position= sf::Vector2f(1000.f, baseHeight);
    m_name="Player 0";
    m_timeout = sf::seconds(0);
    m_connected = true;
    m_ping = 0;
	const sf::Vector2f playerSize = sf::Vector2f(100.0f, 150.0f);
    body.setSize(playerSize);
    body.setPosition(m_position);
    body.setTexture(playerTexture);
    body.setOrigin(playerSize);
//    body.setOrigin(playerSize.x/2, playerSize.y/2);

    const sf::Vector2f bulletSize = sf::Vector2f(20.f, 12.4f);
    bullet.setSize(bulletSize);
    bullet.setPosition(m_position.x+50, m_position.y-50);
    bullet.setTexture(bulletTexture);
//    bullet.setOrigin(bulletSize);
    bullet.setOrigin(bulletSize.x/2, bulletSize.y/2);

    velocity = sf::Vector2f(speed, 0.8f*speed);
}

void Player::Update(float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window)
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

void Player::Draw(sf::RenderWindow &window) {
    window.draw(body);
    window.draw(bullet);
}

void Player::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}
void Player::setName(const std::string& name)
{
    m_name = name;
}

void Player::setTimeout(sf::Time time)
{
    m_timeout = time;
}

void Player::setConnected(bool status)
{
    m_connected = status;
}

void Player::setPing(unsigned short ping)
{
    m_ping = ping;
}

unsigned short Player::getPing() {
    return m_ping;
}
sf::Vector2f Player::getPosition()
{
    return m_position;
}
sf::TcpSocket* Player::getSocket()
{
    return m_socket.get();
}

std::string Player::getName()
{
    return m_name;
}

int Player::getId()
{
    return m_id;
}

sf::Time Player::getTimeout()
{
    return m_timeout;
}
bool Player::isConnected()
{
    return m_connected;
}
