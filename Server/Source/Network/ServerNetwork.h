#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <thread>

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

protected:
    virtual void ProcessTcpPacket(const sf::Packet& receivedPacket) override;

    virtual void ProcessUdpPacket(const sf::Packet& receivedPacket, sf::IpAddress remoteAddress, unsigned short remotePort) override;

private:
    ServerNetwork(const ServerNetwork&) = delete;
    ServerNetwork(ServerNetwork &&) = delete;
    ServerNetwork& operator=(const ServerNetwork&) = delete;
    ServerNetwork&& operator=(ServerNetwork&&) = delete;

private:
    void handleTcpConnectionsThread();

private:
    std::thread m_tcpThread;

};