#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

//////////////////////////////////////////////////////////
// Thirdparty Headers
//////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include <entt/entt.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "Core.h"
#include "Utility.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class ServerNetwork {
public:
    ServerNetwork();
    virtual ~ServerNetwork();

    void StartNetworkThread(sf::IpAddress ip, uint16_t port);
    void ConnectClients();
    void DisconnectClient(sf::TcpSocket*, size_t);
    void ReceivePacket(sf::TcpSocket*, size_t);
    void BroadcastPacket(sf::Packet&, sf::IpAddress, unsigned short);
    void NetworkThreadFunction();

private:
    sf::TcpListener m_listener;
    std::vector<sf::TcpSocket*> m_clients;
    std::thread m_networkThread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_exitThread;
};
