#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <thread>
#include <vector>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "INetwork.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

struct ClientData {
    float timeSinceLastRealMessage = 0.0f;
    sf::IpAddress address = sf::IpAddress::None;
    unsigned short port = 0;

    std::shared_ptr<sf::TcpSocket> tcpSocket;
    std::shared_ptr<sf::UdpSocket> udpSocket;
};

class ServerNetwork : public INetwork {
public:
    explicit ServerNetwork() = default;
    virtual ~ServerNetwork() = default;

    // Start the network communication.
    virtual void Start(const sf::IpAddress& serverIp, unsigned short serverPort) override;

    // Stop the network communication.
    virtual void Stop() override;

    // Update the network logic with the given time interval.
    virtual void Update(float deltaTime) override;

private:
    ServerNetwork(const ServerNetwork&) = delete;
    ServerNetwork(ServerNetwork &&) = delete;
    ServerNetwork& operator=(const ServerNetwork&) = delete;
    ServerNetwork&& operator=(ServerNetwork&&) = delete;

private:
    void HandleTcpConnectionsThread();
    void DisconnectPlayers();
    void Broadcast(sf::Packet& packet, const sf::IpAddress& ignore);
    void HandlePacket(sf::Packet &packet);
    void HandlePacket(sf::Packet& packet, sf::IpAddress ip, unsigned short port);

private:
    std::thread m_tcpThread;
    std::thread m_udpThread;
    std::vector<ClientData> m_connectedClients;
    sf::SocketSelector m_selector;
};