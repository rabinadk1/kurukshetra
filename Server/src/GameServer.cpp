//
// Created by samip on 21/1/19.
//
#include <SFML/Network.hpp>
#include <iostream>
#include "GameServer.h"
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <SFML/Network/TcpSocket.hpp>

GameServer::GameServer(unsigned short port)
{
    m_running = true;
    if(m_listener.listen(port) == sf::Socket::Done)
    {
        std::cout << "Server is started on port: " << port <<  ". Waiting for clients.\n";
        m_selector.add(m_listener);
        m_playersConnected = 0;
        m_dataWaiting = false;
        t0 = std::thread(&GameServer::receive, this);
        t0.detach();
    }
    else
        std::cout << "Error - Failed to bind the port " << port << std::endl;
}

int GameServer::getM_playersConnected() const {
    return m_playersConnected;
}

GameServer::~GameServer(){
    m_running = false;
    socket.disconnect();
    m_listener.close();
}

void GameServer::receive() {
    while (m_running) {
        while (m_playersConnected == 0) {
            if (m_listener.accept(this->socket) == sf::Socket::Done) {
                sf::Packet Name;
                Name<<"Samip";
                socket.send(Name);
                ++m_playersConnected;
            }
        }
        std::cout<<"Data:"<<m_dataWaiting<<std::endl;
        if (this->m_dataWaiting){
            std::cout << "Sending data"<< std::endl;
            if (socket.send(this->m_toSend) != sf::Socket::Done)
                std::cout << "Error sending KeyPress" << std::endl;
            m_mutex.lock();
            this->m_dataWaiting = false;
            m_mutex.unlock();
        }
    }
}

void GameServer::update(sf::Vector2f position2,sf::Vector2f movement,sf::Vector2f bullet, bool isShooting,bool isJumping) {
    sf::Packet keyPress;
    keyPress<<position2.x<<position2.y<<movement.x<<movement.y<<bullet.x<<bullet.y<<isShooting<<isJumping;
    std::cout<<position2.x;
        this->m_toSend = keyPress;
        m_mutex.lock();
        this->m_dataWaiting = true;
        m_mutex.unlock();
}

