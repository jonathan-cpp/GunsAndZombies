#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <SFML/Network.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class INetwork {
public:
    virtual ~INetwork() = default;
    
    // Abstract Interface
    virtual void Start(const sf::IpAddress& serverIp, unsigned short serverPort) = 0;
    virtual void Stop() = 0;
    virtual void Update(float deltaTime) = 0;

    // Public Functions
    void ReceivePacket(sf::TcpSocket& socket, size_t clientId) {}
    void ReceivePacket(sf::UdpSocket& socket, size_t clientId) {}
    void SendPacket(sf::Packet &packet, sf::TcpSocket* socket) {}
    void SendPacket(sf::Packet &packet, sf::UdpSocket* socket) {}

private:
    explicit INetwork() = default;
    INetwork(const INetwork&) = delete;
    INetwork(INetwork &&) = delete;
    INetwork& operator=(const INetwork&) = delete;
    INetwork&& operator=(INetwork&&) = delete;

private:
    // Private Functions

private:
    // Member Variables
};

// Client-specific networking functionalities
class ClientNetwork {
public:
    explicit ClientNetwork() = default;
    virtual ~ClientNetwork() = default;
    
    // Public Functions
    void Start(const sf::IpAddress& serverIp, unsigned short serverPort) override {}
    void Stop() override {}
    void Update(float deltaTime) override {}

private:
    ClientNetwork(const ClientNetwork&) = delete;
    ClientNetwork(ClientNetwork &&) = delete;
    ClientNetwork& operator=(const ClientNetwork&) = delete;
    ClientNetwork&& operator=(ClientNetwork&&) = delete;

private:
    // Private Functions

private:
    // Member Variables
};

// Server-specific networking functionalities
class ServerNetwork {
public:
    explicit ServerNetwork() = default;
    virtual ~ServerNetwork() = default;
    
    // Public Functions
    void Start(const sf::IpAddress& serverIp, unsigned short serverPort) override {}
    void Stop() override {}
    void Update(float deltaTime) override {}

    void SyncPlayers(float deltaTime) {}
	void DisconnectPlayer(size_t position) {}
	void Prediction(float deltaTime) {}
    void BroadcastPacket(sf::Packet& packet, sf::IpAddress excludeAddress, unsigned short port) {}

private:
    ServerNetwork(const ServerNetwork&) = delete;
    ServerNetwork(ServerNetwork &&) = delete;
    ServerNetwork& operator=(const ServerNetwork&) = delete;
    ServerNetwork&& operator=(ServerNetwork&&) = delete;

private:
    // Private Functions

private:
    // Member Variables
};