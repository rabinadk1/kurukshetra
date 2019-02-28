//
// Created by samip on 21/1/19.
//
#include <SFML/Network.hpp>
#include <iostream>
#include "GameClient.h"
#include <SFML/Graphics.hpp>
#include <Global.h>


GameClient::GameClient(const sf::IpAddress& ip, const short& port):recievedData({sf::Vector2f(0.f,0.f),sf::Vector2f(0.f,0.f),sf::Vector2f(0.0f, 0.0f), false})
{
m_connected=false;
m_running2=true;
//connection(ip,port);
    t1=std::thread(&GameClient::connection,this,ip,port);
    t1.detach();
}

GameClient::~GameClient() {
m_running2=false;
m_socket.disconnect();
}

void GameClient::connection(const sf::IpAddress& ip, const short& port)
{
    while (!m_connected){
        if (m_socket.connect(ip, port, sf::seconds(15)) != sf::Socket::Done)
        {
            std::cout << "Error connecting to server" << std::endl;
        }
        else {
            m_connected = true;
            std::cout << "Connected to the server" << std::endl;
            sf::Packet NameP;
            m_socket.receive(NameP);
            m_mutex.lock();
            NameP>>Name;
            m_mutex.unlock();
        }
    }
    while (this->m_running2) {
        this->recievedData  = recieveData();
    }

}

const std::string &GameClient::getName() const {
    return Name;
}

const struct clientInfo &GameClient::getRecievedData() const {
    return recievedData;
}

struct clientInfo GameClient::recieveData(){
    m_socket.setBlocking(true);
//    while(m_running2)
//    {
        struct clientInfo c1;
        sf::Packet Sam;

        if (m_socket.receive(Sam) == sf::Socket::Done) {
            Sam>>c1.bodyPosition.x>>c1.bodyPosition.y>>c1.bodyMovement.x>>c1.bodyMovement.y>>c1.bullet.x>>c1.bullet.y>>c1.isshooting>>c1.shootWithTime>>c1.isJumping;
            //std::cout << moveX;
            return c1;
        } else
        {
            std::cout << "No data recieved";
            struct clientInfo c1={sf::Vector2f(0.f,0.f),sf::Vector2f(0.f,0.f),sf::Vector2f(0.f,0.f),false, false};
            return c1;
        }
   // }
}
