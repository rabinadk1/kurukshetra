//
// Created by safal on 13/2/19.
//

#include <iostream>
#include <cmath>
#include <GameServer.h>
#include "Enemy.h"
#include "Player.h"

Player::Player()
	:sounds(Sounds::soundNumber), isPlayer(true)
{
	sounds.load(Sounds::gunShot, "../Media/Audio/gunShot0.wav");
	gunSound.setBuffer(sounds.get(Sounds::gunShot));
}

void Player::SetData(sf::Texture *playerTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
	animation.SetData(playerTexture, imageCount, switchTime);
	row = 0;
	faceRight = true;
	isJumping = isShooting = checkforMouse = false;
	health = 100;
	bulletVelocity = moveDirection = sf::Vector2f(0.f, 0.f);

	const sf::Vector2f playerSize = sf::Vector2f(250.0f, 250.0f);
	body.setSize(playerSize);
	body.setPosition(position);
	body.setTexture(playerTexture);
	body.setOrigin(playerSize);

	//TODO set origin to the place where bullet exits
//    body.setOrigin(playerSize.x/2, playerSize.y/2);
	velocity = sf::Vector2f(2*speed, 1.5f*speed);
}
void Player::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape &sky, sf::Text *info)
{
	static sf::Vector2f movement(0.f, 0.f);
	static float localVelocity = velocity.y;
	const float g = 9.81f;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= velocity.x * deltaTime;
	//NOTE: Make a collision detection by comparing the positions of the wall and player
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += velocity.x * deltaTime;
	if (body.getPosition().x <= leftExtremePoint + body.getSize().x)
	{
		if (movement.x<0)
			movement.x = 0;
		body.setPosition(leftExtremePoint+body.getSize().x, body.getPosition().y);
	}
	else if(body.getPosition().x >= rightExtremePoint)
	{
		if(movement.x>0)
			movement.x = 0;
		body.setPosition(rightExtremePoint, body.getPosition().y);
	}
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and isUp)
//        movement.y += velocity.x * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        isJumping = true;

//	static sf::Vector2f mousePos;
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);
	sf::IntRect viewport = gameView.GetViewport(window);
	sf::Vector2f mousePos;
	sf::Vector2f localBulletPos;
	checkforMouse = viewport.contains(pixelMousePos);
	if (checkforMouse)
	{
		mousePos = window.mapPixelToCoords(pixelMousePos);
		checkforMouse = checkforMouse and mousePos.y <= baseHeight;
		if (checkforMouse)
		{
			if (faceRight)
				localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
			else
				localBulletPos.x = body.getPosition().x - body.getSize().y*0.8f;
			localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;
			line[0] = sf::Vertex(localBulletPos);
			line[1] = sf::Vertex(mousePos);
		}
	}
	if (not isShooting and sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (checkforMouse)
		{
				sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
				double distance = sqrt(double(displacement.x * displacement.x + displacement.y * displacement.y));

				moveDirection = sf::Vector2f(float(displacement.x / distance), float(displacement.y / distance));

				bulletVelocity = sf::Vector2f(4*velocity.x * moveDirection.x*deltaTime, 4*velocity.y * moveDirection.y* deltaTime);
				isShooting = true;
				clock.restart();
		}
	}
	if (isShooting and clock.getElapsedTime().asSeconds()>=0.2f )
	{
		gunSound.play();
		bullets.emplace_back(Bullet(bulletTexture, sf::Vector2f(20.f, 12.4f), body.getPosition(), bulletVelocity));
		isShooting = false;
		clock.restart();
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
	if(isJumping)
	    row = 2;
	if(isShooting)
	{
		row = 3;
		faceRight = bulletVelocity.x>0;
	}

	gameView.Move(movement);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	gameView.showInfo(&info[0], body);

    if (isJumping)
	{
		movement.y = -localVelocity * deltaTime;
		localVelocity -= g;
	}
	else
		movement = sf::Vector2f(0.f,0.f);
}

void Player::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape &sky, sf::Text *info, GameServer& server)
{
	static sf::Vector2f movement(0.f, 0.f);
	static float localVelocity = velocity.y;
	const float g = 9.81f;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= velocity.x * deltaTime;
	//NOTE: Make a collision detection by comparing the positions of the wall and player
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += velocity.x * deltaTime;
	if (body.getPosition().x <= leftExtremePoint + body.getSize().x)
	{
		if (movement.x<0)
			movement.x = 0;
		body.setPosition(leftExtremePoint+body.getSize().x, body.getPosition().y);
	}
	else if(body.getPosition().x >= rightExtremePoint)
	{
		if(movement.x>0)
			movement.x = 0;
		body.setPosition(rightExtremePoint, body.getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		isJumping = true;

	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);
	sf::IntRect viewport = gameView.GetViewport(window);
	sf::Vector2f mousePos;
	sf::Vector2f localBulletPos;
	checkforMouse = viewport.contains(pixelMousePos);
	if (checkforMouse)
	{
		mousePos = window.mapPixelToCoords(pixelMousePos);
		checkforMouse = checkforMouse and mousePos.y <= baseHeight;
		if (checkforMouse)
		{
			if (faceRight)
				localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
			else
				localBulletPos.x = body.getPosition().x - body.getSize().y*0.8f;
			localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;
			line[0] = sf::Vertex(localBulletPos);
			line[1] = sf::Vertex(mousePos);
		}
	}
	if (not isShooting and sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (checkforMouse)
		{
			sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
			double distance = sqrt(double(displacement.x * displacement.x + displacement.y * displacement.y));

			moveDirection = sf::Vector2f(float(displacement.x / distance), float(displacement.y / distance));

			bulletVelocity = sf::Vector2f(4*velocity.x * moveDirection.x*deltaTime, 4*velocity.y * moveDirection.y* deltaTime);
			isShooting = true;
			clock.restart();
		}
	}
	bool playerIsShooting = isShooting and clock.getElapsedTime().asSeconds()>=0.2f;
	if (playerIsShooting)
	{
		gunSound.play();
		bullets.emplace_back(Bullet(bulletTexture, sf::Vector2f(20.f, 12.4f), body.getPosition(), bulletVelocity));
		isShooting = false;
		clock.restart();
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
	if(isJumping)
		row = 2;
	if(isShooting)
	{
		row = 3;
		faceRight = bulletVelocity.x>0;
	}

    server.update(body.getPosition(),movement,bulletVelocity, playerIsShooting,isJumping);
	gameView.Move(movement);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	gameView.showInfo(&info[0], body);

	if (isJumping)
	{
		movement.y = -localVelocity * deltaTime;
		localVelocity -= g;
	}
	else
		movement = sf::Vector2f(0.f,0.f);

}

void Player::Draw(sf::RenderWindow &window, Enemy& enemy) {
//	if (isDead())
//	{
//		std::cout<<"Player died successfully!"<<std::endl;
//		exit(0);
//	}
	window.draw(body);
//	std::cout << body.getPosition().x << std::endl;
	for (auto &bullet : bullets)
	{
		bullet.draw(window);
		bullet.fire();
	}
	if(checkforMouse)
		window.draw(line, 2, sf::Lines);
	for (int i = 0; i < int(bullets.size()); i++)
	{
		if (HitCheck(enemy, bullets[i]))
			bullets.erase(bullets.begin() + i--);
	}
}

void Player::SetPosition(sf::Vector2f position) {
	body.setPosition(position);
}

bool Player::HitCheck(Enemy& enemy, Bullet& bullet)
{
	if(enemy.GetCollider().CheckCollision(Collider(bullet.getBullet())))
	{
		enemy.health -= 20;
		return true;
	}
	return false;
}

bool Player::isUp(sf::RectangleShape &shape, float &baseHeight)
{
	return shape.getPosition().y <= baseHeight;
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

void Player::collisionTest(Player &player, std::vector<Platform> &walls, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint) {
	if(player.getPosition().x < leftExtremePoint + 2000)
	{
		for(int i = 0; i<8; i++)
		{
			if(player.GetCollider().CheckCollision(walls[i].GetCollider()))
				std::cout << "collided with wall " << i + 1 << std::endl;
		}
	}
}


