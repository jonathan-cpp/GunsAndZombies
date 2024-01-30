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

class ClientNetwork {
public:
    ClientNetwork();
    virtual ~ClientNetwork(); 

    void StartNetworkThread(sf::IpAddress ip, uint16_t port);
    void ReceivePackets(sf::TcpSocket* socket);
    void SendPacket(sf::Packet& packet);
    void NetworkThreadFunction();

private:
    sf::TcpSocket m_tcpSocket;
    std::thread m_networkThread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_exitThread;

    sf::Packet m_lastPacket;
};