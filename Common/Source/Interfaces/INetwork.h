#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <any>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <SFML/Network.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "Core.h"

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

    // Start the network communication, connecting to the specified server.
    virtual void Start(const sf::IpAddress& serverIp, unsigned short serverPort) = 0;

    // Stop the network communication, stopping the server.
    virtual void Stop() = 0;

    // Update the network logic with the given time interval.
    virtual void Update(float deltaTime) = 0;

protected: 
    // Function to handle the reception of TCP packets.
    // It evokes ProcessTcpPacket upon packet received.
    void ReceiveTcpPacket();

    // Function to handle the reception of UDP packets.
    // It evokes ProcessUdpPacket upon packet received.
    void ReceiveUdpPacket();

    // Send a TCP packet to the specified TCP socket.
    void SendTcpPacket(sf::Packet &packet, std::shared_ptr<sf::TcpSocket> socket);

    // Send a UDP packet to the specified UDP socket.
    void SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort);

    // Helper function to check socket status and handle errors
    // Returns true if the status is Socket::Done (success), false otherwise.
    bool CheckSocketStatus(sf::Socket::Status status);

    // Virtual function to be implemented by derived classes
    // Process the received message. Derived classes should implement this function to define
    // how to handle the received TCP packets.
    virtual void ProcessTcpPacket(const sf::Packet& receivedPacket) = 0;

    // Virtual function to be implemented by derived classes
    // Process the received message. Derived classes should implement this function to define
    // how to handle the received UDP packets.
    virtual void ProcessUdpPacket(const sf::Packet& receivedPacket, sf::IpAddress remoteAddress, unsigned short remotePort) = 0;

    // Serialize higher-level data into a SFML Packet for transmission.
    virtual sf::Packet SerializeData(const std::any& data) const {}

    // Deserialize an SFML Packet into higher-level data.
    virtual std::any DeserializeData(const sf::Packet& packet) const {}

private:
    explicit INetwork() = default;
    INetwork(const INetwork&) = delete;
    INetwork(INetwork &&) = delete;
    INetwork& operator=(const INetwork&) = delete;
    INetwork&& operator=(INetwork&&) = delete;

protected:
    std::shared_ptr<sf::TcpSocket> m_tcpSocket;
    std::shared_ptr<sf::UdpSocket> m_udpSocket;

private:

};