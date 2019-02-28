//
// Created by samip on 25/2/19.
//

#include <iostream>
#include <cmath>
#include <GameServer.h>
#include "Player.h"
#include "Global.h"
#include "Enemy.h"

Enemy::Enemy()
	:sounds(Sounds::soundNumber)
{
	sounds.load(Sounds::gunShot, "../Media/Audio/gunShot0.wav");
	gunSound.setBuffer(sounds.get(Sounds::gunShot));
}

void Enemy::SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
	animation.SetData(EnemyTexture, imageCount, switchTime);
	row = 0;
	faceRight = true;
	isJumping = isShooting = false;
	health = 100;
	bulletVelocity = moveDirection = sf::Vector2f(0.f, 0.f);

	const sf::Vector2f EnemySize = sf::Vector2f(250.0f, 250.0f);
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

void Enemy::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window, sf::RectangleShape& sky, sf::Text *info, GameClient& client)
{
	static sf::Vector2f movement2(0.f, 0.f);
	static float localVelocity = velocity.y;
	const float g = 9.81f;
	SetPosition(client.getRecievedData().bodyPosition);
//movement2=client.getRecievedData().bodyMovement;
	isShooting= client.getRecievedData().isshooting;
	if (isShooting)
	{
		bulletVelocity=client.getRecievedData().bullet;

		row = 3;
		faceRight = bulletVelocity.x>0;

		gunSound.play();
		sf::Vector2f localBulletPos;
		if (faceRight)
			localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
		else
			localBulletPos.x = body.getPosition().x - body.getSize().y*0.8f;
		localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;
		bullets.emplace_back(bulletTexture, sf::Vector2f(20.f, 12.4f), localBulletPos, bulletVelocity);
		isShooting = false;
	}
//	}

	if (not isUp(body, baseHeight))
	{
		body.setPosition(body.getPosition().x, baseHeight);
		isJumping = false;
		localVelocity = velocity.y;
	}

	if(client.getRecievedData().bodyMovement.x == 0)
		row = 0;
	else
	{
		row = 1;
		faceRight = faceRight || client.getRecievedData().bodyMovement.x > 0;
	}

//    std::cout<<movement2.x<<movement2.y;
	// gameView.move(movement2);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement2);
	gameView.showInfo(&info[1], body);
//	if (isJumping)
//	{
//		movement2.y = -localVelocity * deltaTime;
//		localVelocity -= g;
//	}
//	else
//		movement2 = sf::Vector2f(0.f,0.f);
    if(client.getRecievedData().isJumping)
        row = 2;
}
void Enemy::Draw(sf::RenderWindow &window, Player& player) {
//	if (isDead())
//	{
//		std::cout<<"Enemy died successfully!"<<std::endl;
//		exit(0);
//	}
	window.draw(body);
//	std::cout << body.getPosition().x << std::endl;
	for (auto &bullet : bullets)
	{
		bullet.draw(window);
		bullet.fire();
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
		player.health -= 20;
		return true;
	}
	return false;
}

bool Enemy::isUp(sf::RectangleShape &shape, float &baseHeight) {
	return shape.getPosition().y <= baseHeight;
}