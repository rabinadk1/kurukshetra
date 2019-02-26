//
// Created by maverick on 25/2/19.
//

#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Texture *bulletTexture, sf::Vector2f bulletSize, sf::Vector2f bulletPos, sf::Vector2f bulletVelocity)
	:velocity(bulletVelocity)
{
	bullet.setSize(bulletSize);
	bullet.setPosition(bulletPos);
	bullet.setTexture(bulletTexture);
//    bullet.setOrigin(bulletSize);
	bullet.setOrigin(bulletSize.x/2, bulletSize.y/2);
}

void Bullet::fire()
{
	std::cout<<velocity.x<<" "<<velocity.y<<std::endl;
	bullet.move(velocity);
}

void Bullet::draw(sf::RenderWindow &window)
{
	window.draw(bullet);
}
