//
// Created by samip on 25/2/19.
//

#include <iostream>
#include <cmath>
#include <GameServer.h>
#include "Player.h"

#include "Enemy.h"

Enemy::Enemy(std::unique_ptr<sf::TcpSocket> *socket, int id) {
    m_socket = std::move(*socket);
    m_id=id;
}

void Enemy::SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
    animation.SetData(EnemyTexture, imageCount, switchTime);
    row = 0;
    faceRight = true;
    isJumping = isShooting = false;
    health = mana = 100;
    bulletVelocity = moveDirection = sf::Vector2f(0.f, 0.f);

    const sf::Vector2f EnemySize = sf::Vector2f(100.0f, 150.0f);
    body.setSize(EnemySize);
    body.setPosition(position);
    body.setTexture(EnemyTexture);
    body.setOrigin(EnemySize);
//    body.setOrigin(EnemySize.x/2, EnemySize.y/2);

//	const sf::Vector2f bulletSize = sf::Vector2f(20.f, 12.4f);
//	bullet.setSize(bulletSize);
//	bullet.setPosition(position.x+50, position.y-50);
//	bullet.setTexture(bulletTexture);
////    bullet.setOrigin(bulletSize);
//	bullet.setOrigin(bulletSize.x/2, bulletSize.y/2);

    velocity = sf::Vector2f(2*speed, 1.5f*speed);
}

void Enemy::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window, sf::Vector2f position)
{
    static sf::Vector2f movement2(0.f, 0.f);
    sf::Vector2f bulletmovement2(0.f, 0.f);
    static float localVelocity = velocity.y;
    const float g = 9.81f;
//    if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//        movement2.x -= velocity.x * deltaTime;
//    if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        movement2.x += velocity.x * deltaTime;
////    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
////        movement2.y += velocity.x * deltaTime;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//    {
//        isJumping = true;
//    }
    movement2=position;
    static sf::Vector2f mousePos;
    if (not isShooting and sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);

        sf::IntRect viewport = gameView.GetViewport(window);
        if (viewport.contains(pixelMousePos))
        {
            mousePos = window.mapPixelToCoords(pixelMousePos);
//            std::cout<<mousePos.y<<" "<<body.getPosition().y<<std::endl;
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
//			bulletmovement2.x += bulletVelocity.x * deltaTime;
//			bulletmovement2.y += bulletVelocity.y * deltaTime;
//			bulletVelocity.y += g;
//		}
//	}
    if (isShooting)
    {
        Bullet newBullet(bulletTexture, sf::Vector2f(20.f, 12.4f), body.getPosition(), bulletVelocity);
        bullets.push_back(newBullet);
        isShooting = false;
    }
//	}

    if (not isUp(body, baseHeight))
    {
        body.setPosition(body.getPosition().x, baseHeight);
        isJumping = false;
        localVelocity = velocity.y;
    }

    if(movement2.x == 0)
        row = 0;
    else
    {
        row = 1;
        faceRight = movement2.x > 0;
    }

//    std::cout<<movement2.x<<movement2.y;
   // gameView.move(movement2);
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement2);
    if (isJumping)
    {
        movement2.y = -localVelocity * deltaTime;
        localVelocity -= g;
    }
    else
        movement2 = sf::Vector2f(0.f,0.f);
}
void Enemy::Draw(sf::RenderWindow &window, Player& player) {
//	if (isDead())
//	{
//		std::cout<<"Enemy died successfully!"<<std::endl;
//		exit(0);
//	}
    window.draw(body);
//	std::cout << body.getPosition().x << std::endl;
    for (int i = 0; i < int(bullets.size()); i++)
    {
        bullets[i].draw(window);
        bullets[i].fire();
    }

    for (int i = 0; i < int(bullets.size()); i++)
    {
        if (HitCheck(player, bullets[i]))
            bullets.erase(bullets.begin() + i--);
    }
}

void Enemy::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}

bool Enemy::HitCheck(Player& player, Bullet& bullet)
{
    if(player.GetCollider().CheckCollision(Collider(bullet.getBullet())))
    {
        player.health -= 50;
        return true;
    }
    return false;
}

bool Enemy::isUp(sf::RectangleShape &shape, float &baseHeight) {
    return shape.getPosition().y <= baseHeight;
}

void Enemy::setName(const std::string& name)
{
    m_name = name;
}

void Enemy::setTimeout(sf::Time time)
{
    m_timeout = time;
}

void Enemy::setConnected(bool status)
{
    m_connected = status;
}

void Enemy::setPing(unsigned short ping)
{
    m_ping = ping;
}

unsigned short Enemy::getPing() {
    return m_ping;
}
sf::Vector2f Enemy::getPosition()
{
    return m_position;
}
sf::TcpSocket* Enemy::getSocket()
{
    return m_socket.get();
}

std::string Enemy::getName()
{
    return m_name;
}

int Enemy::getId()
{
    return m_id;
}

sf::Time Enemy::getTimeout()
{
    return m_timeout;
}

bool Enemy::isConnected()
{
    return m_connected;
}
