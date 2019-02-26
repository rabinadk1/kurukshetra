//
// Created by samip on 21/1/19.
//
#include <SFML/Network.hpp>
#include <iostream>
#include "GameServer.h"
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <SFML/Network/TcpSocket.hpp>

GameServer::GameServer(unsigned short port):recievedData(0.f,0.f)
{
    m_running = true;
    if(m_listener.listen(port) == sf::Socket::Done)
    {
        std::cout << "Server is started on port: " << port <<  ". Waiting for clients.\n";
        m_selector.add(m_listener);
        m_maxPlayers = 2;
        m_playersConnected = 0;
        m_currentPlayerId = 0;
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
}


//void GameServer::setPlayerList(std::vector<Player> *players)
//{
//    m_playerList = players;
//}

void GameServer::receive() {

    while (m_running) {
        if (m_selector.wait()) {
            if (m_selector.isReady(m_listener)) {
                // Creating the socket that will wait for new connections
//                 sf::TcpSocket tempSocket;
                //std::unique_ptr<sf::TcpSocket> tempSocket(new sf::TcpSocket);
                // If a new client is connected this code executes
                if (m_listener.accept(socket) == sf::Socket::Done) {

                    std::cout << "Connected";
                    // std::lock_guard<std::mutex> guard(m_mutex);

                    //  m_playerList.emplace_back(Enemy(&tempSocket,m_currentPlayerId));
                    // m_selector.add(*m_playerList.back().getSocket());
                    ++m_playersConnected;
                    // std::cout << m_playersConnected;
                    t1 = std::thread(&GameServer::recieveData, this);
                    t1.detach();
                    t2 = std::thread(&GameServer::update, this);
                    t2.detach();
//                        // TODO Create a function that send the id
                }
                else
                    std::cout<<"Can't connect";
            }
        }
    }
}

void GameServer::update() {
while (m_running)
{
    sf::Packet keyPress;
    keyPress<<position.x<<position.y;
    std::cout<<position.x;
    if (socket.send(keyPress) != sf::Socket::Done)
        std::cout << "Error sending KeyPress" << std::endl;
}

}

void GameServer::setPosition(const sf::Vector2f &position) {
    GameServer::position = position;
}

const sf::Vector2f &GameServer::getRecievedData() const {
    return recievedData;

}

sf::Vector2f GameServer::recieveData(){
    while(m_running)
    {
        float moveX,moveY;
        sf::Packet Sam;
        socket.setBlocking(true);
        if (socket.receive(Sam) == sf::Socket::Done) {
            Sam>>moveX>>moveY;
            sf::Vector2f position=sf::Vector2f(moveX,moveY);
            recievedData=position;
        } else
        {
            std::cout << "Some Error occured";
            sf::Vector2f position=sf::Vector2f(0.f,0.f);
            recievedData= position;
        }
    }
}