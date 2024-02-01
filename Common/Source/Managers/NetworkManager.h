#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <SFML/Network.hpp>
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
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class NetworkManager {
public:
    explicit NetworkManager();
    virtual ~NetworkManager();

    // Client-related functions
    void StartClient(const sf::IpAddress& serverIp, uint16_t serverPort);
    void StopClient();
    void ClientThread();

    // Server-related functions
    void StartServer(uint16_t port);
    void StopServer();
    void HandleClientConnections();
    void HandleClientPackets();

    // Common functions
    void BroadcastPacket(sf::Packet& packet, sf::IpAddress excludeAddress, unsigned short port);
    void ReceivePacket(sf::TcpSocket& socket, size_t clientId);
    void SendPacket(sf::Packet &packet, sf::TcpSocket* socket);
    void DisconnectClient(size_t position);
    void Update(float deltaTime);

private:
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager(NetworkManager &&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager&& operator=(NetworkManager&&) = delete;

private:
    // Private Functions

private:
    sf::TcpSocket m_clientSocket;
    sf::TcpListener m_serverListener;
    std::vector<UniquePtr<sf::TcpSocket>> m_clients;
    std::thread m_networkThread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_exitThread;
};