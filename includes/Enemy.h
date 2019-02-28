//
// Created by samip on 25/2/19.
//
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
#include "GameClient.h"
#include "ResourceHolder.h"
#include <SFML/Audio.hpp>
#include <vector>

class Player;

class Enemy {
public:
    Enemy();
    void SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
    void Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window, sf::RectangleShape& sky, sf::Text* info, GameClient& client);
    void Draw(sf::RenderWindow& window, Player& player);
    Collider GetCollider() { return Collider(body); }
    void SetPosition(sf::Vector2f position);
	bool isDead(){ return health<=0;}
private:
	bool HitCheck(Player& player, Bullet& bullet);
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
    sf::Clock clock;
    bool m_connected;
    int m_id;
    unsigned short m_ping;
    sf::Vector2f velocity, bulletVelocity, moveDirection;
    std::vector <Bullet> bullets;
    friend class Player;
public:
    int health;
};
