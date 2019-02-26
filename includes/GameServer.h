//
// Created by samip on 21/1/19.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H
#include <SFML/System/Time.hpp>
#include <SFML/Network.hpp>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <SFML/Network/TcpSocket.hpp>
#include <Enemy.h>

enum SIGNAL_SEND
{
    PING = 0,
    SERVER_FULL = 51,
    CLIENT_ID,
//    PLAYER_LIST,
//    PLAYER_CONNECTED,
//    PLAYER_DISCONNECTED,
//    CLIENT_POSITION,
//    ENEMY_POSITION,
//    TEXT_MESSAGE
};

enum SIGNAL_RECEIVE
{
//    PING_REC,
//    CLIENT_NAME,
//    CLIENT_VELOCITY,
//    CLIENT_DISCONNECTED,
//    PLAYER_LIST_REQUEST,
//    TEXT_MESSAGE_REC
};


class GameServer {
public:
    GameServer(unsigned short port);
    ~GameServer();

    void receive();
    void update(sf::Keyboard::Key key);
    void update(sf::Vector2f position);
//
//    void updateTick();
//    void updateWorld(sf::Time dt);

    //  void setPlayerList(std::vector<Player> *players);

    int getM_playersConnected() const;

private:
    bool m_running;

    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;


    // Server settings
    unsigned short m_port;
    unsigned short m_maxPlayers;

    // Maybe add here "ticks" like in the counter strike.
    // Then the user should get the number of ticks and run it on the same speed on his simulation


    // Variables
    int32_t m_playersConnected;
    int32_t m_currentPlayerId;

    std::vector<Enemy> m_playerList;
    //   std::queue<sf::Packet> m_receivedPackets;

    //   char m_tmp[1400];

    std::thread t0;
    std::mutex m_mutex;


    // Map
    //  LevelManager m_currentLevel;
};

#endif //UNTITLED_SERVER_H
