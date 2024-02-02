#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



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

class ClientNetwork : public INetwork {
public:
    explicit ClientNetwork() = default;
    virtual ~ClientNetwork() = default;

    // Start the network communication.
    virtual void Start(const sf::IpAddress& serverIp, unsigned short serverPort) override;

    // Stop the network communication.
    virtual void Stop() override;

    // Update the network logic with the given time interval.
    virtual void Update(float deltaTime) override;

protected:
    virtual void ProcessTcpPacket(const sf::Packet& receivedPacket) override {}

    virtual void ProcessUdpPacket(const sf::Packet& receivedPacket, sf::IpAddress remoteAddress, unsigned short remotePort) override {}

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