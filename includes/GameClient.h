//
// Created by samip on 23/1/19.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "Global.h"
#include <mutex>

class GameClient {

public:
    GameClient(const sf::IpAddress& ip, const short& port);
    void connection(const sf::IpAddress& ip, const short& port);

    struct clientInfo recieveData();
    bool isConnected() { return m_connected; }
    virtual ~GameClient();
    const struct clientInfo &getRecievedData() const;
private:
    sf::TcpSocket m_socket;
    bool m_connected;
    bool m_running2;
    struct clientInfo recievedData;
    sf::Vector2f position;
//        std::vector<InputData> m_input_sequence_list;
//        ServerData m_server_real_pos;
//        sf::Uint64 m_current_input_id;

    sf::Int64 m_ping_ms;
    sf::Int64 m_client_time_sent;
    sf::Int64 m_offset;
    std::mutex m_mutex;
    std::thread t1;
    sf::Clock m_clock;
//        Player* m_player;
//        std::vector<Enemy>* m_enemies;
//        TabOverlay* m_tabOVerlay;
//        Chat* m_chat;

    std::string m_textMessage;
};
#endif //UNTITLED_CLIENT_H
