//
// Created by safal on 13/2/19.
//

#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include "Animation.h"
#include "Collider.h"
#include "GameServer.h"
#include "Bullet.h"
#include "Camera.h"
#include "Platform.h"
#include "../Server/src/ResourceHolder.cpp"
#include <SFML/Audio.hpp>
#include <vector>

class Enemy;

class Player {
public:
	Player();
    void SetData(sf::Texture *playerTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	void Update(sf::Texture* bulletTexture , float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape& sky, GameServer& server);
	void Update(sf::Texture* bulletTexture , float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape& sky);
	void Draw(sf::RenderWindow& window, Enemy& enemy);
    Collider GetCollider() { return Collider(body); }
    sf::RectangleShape& GetBody() { return body;}
    void SetPosition(sf::Vector2f position);
    void collisionTest(Player& player, std::vector<Platform>& walls, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint);
    void setName(const std::string& name);
    void setTimeout(sf::Time time);
    void setConnected(bool status);
    void setPing(unsigned short ping);
    sf::Vector2f getPosition();
    sf::TcpSocket* getSocket();
    sf::Time getTimeout();
    std::string getName();
    bool isConnected();
    unsigned short getPing();
    int getId();
    bool isDead(){ return health<=0;}

private:
	bool HitCheck(Enemy& enemy, Bullet& bullet);
	bool isUp(sf::RectangleShape& shape, float& baseHeight);

private:
    sf::RectangleShape body;
    Animation animation;
	ResourceHolder <sf::SoundBuffer, Sounds::ID> sounds;
	sf::Sound gunSound;
    unsigned row;
    bool faceRight, isJumping, isShooting;
    sf::Vector2f m_position;
    sf::Time m_timeout;
    std::string m_name;
    std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
    bool m_connected;
    int m_id;
    unsigned short m_ping;
    sf::Vector2f velocity, bulletVelocity, moveDirection;
    std::vector <Bullet> bullets;
    sf::Clock clock;
public:
	int health;
};
