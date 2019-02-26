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
        std::cout << "Server is started on port: " << port <<  ". Waiting for clients.\n";
    else
        std::cout << "Error - Failed to bind the port " << port << std::endl;
    m_selector.add(m_listener);
    m_maxPlayers = 2;
    m_playersConnected = 0;
    m_currentPlayerId = 0;
    t0 = std::thread(&GameServer::receive, this);
    t0.detach();

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
                // sf::TcpSocket tempSocket;
                std::unique_ptr<sf::TcpSocket> tempSocket(new sf::TcpSocket);
                // If a new client is connected this code executes
                if (m_listener.accept(*tempSocket) == sf::Socket::Done) {
                    if (m_playersConnected < m_maxPlayers) //if server is not full
                    {
                        std::cout << "Connected";
                        std::lock_guard<std::mutex> guard(m_mutex);

                        m_playerList.emplace_back(Enemy(&tempSocket,m_currentPlayerId));
                        m_selector.add(*m_playerList.back().getSocket());
                        ++m_playersConnected;
                        std::cout << m_playersConnected;
//                        // TODO Create a function that send the id
                        sf::Packet outPacket;
                        //      outPacket << SIGNAL_SEND::CLIENT_ID;
                        outPacket << m_currentPlayerId;
//
//                        //Send client id
                        if (m_playerList.back().getSocket()->send(outPacket) != sf::Socket::Done)
                            std::cout << "Error sending player index" << std::endl;
                        ++m_currentPlayerId;
                    } else // Server is full
                    {
                        sf::Packet outPacket;
                        outPacket << SIGNAL_SEND::SERVER_FULL;

                        if (tempSocket->send(outPacket) != sf::Socket::Done)
                            std::cout << "Error sending server is full message!" << std::endl;

                        std::cout << "User tried to connect but the server was full!" << std::endl;
                    }
                } else {
                    // TODO look into this, test if it works on multiple computers with locking the mutex here
                    std::lock_guard<std::mutex> guard2(m_mutex);
                    for (auto &player : m_playerList) {
                        if (m_selector.isReady(*player.getSocket())) {
                            sf::Packet received;
                            if (player.getSocket()->receive(received) == sf::Socket::Done) {
                                // If mutex is locked here it doesn't work for the first but it works for all other
                                //std::lock_guard<std::mutex> guard2(m_mutex);
                                // Add the element on the end of the queue
                                //        m_receivedPackets.push(received);
                            }
                        }
                    }
                }
            }
        }
    }
}
void GameServer::update(sf::Keyboard::Key key) {
    sf::Packet keyPress;
    int32_t keyCode= static_cast<int32_t>(key);
    keyPress<<keyCode;
    if (m_playerList.back().getSocket()->send(keyPress) != sf::Socket::Done)
        std::cout << "Error sending KeyPress" << std::endl;
    ++m_currentPlayerId;

}
void GameServer::update(float position) {
    sf::Packet keyPress;
    //int32_t keyCode= static_cast<int32_t>(key);
    keyPress<<position;
    if (m_playerList.back().getSocket()->send(keyPress) != sf::Socket::Done)
        std::cout << "Error sending KeyPress" << std::endl;
    ++m_currentPlayerId;
}