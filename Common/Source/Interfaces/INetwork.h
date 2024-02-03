#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <any>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <SFML/Network.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "EventSystem.h"

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
    explicit INetwork() = default;
    virtual ~INetwork() = default;

    // Start the network communication.
    virtual void Start(const sf::IpAddress& serverIp, unsigned short serverPort) = 0;

    // Stop the network communication.
    virtual void Stop() = 0;

    // Update the network logic with the given time interval.
    virtual void Update(float deltaTime) = 0;

    // Function Callbacks
    DECLARE_EVENT(PeerConnectedEvent, sf::TcpSocket*);
    PeerConnectedEvent OnPeerConnected;

    DECLARE_EVENT(PeerDisconnectedEvent, sf::TcpSocket*);
    PeerDisconnectedEvent OnPeerDisconnected;

    DECLARE_EVENT(TcpPacketReceivedEvent, sf::Packet&);
    TcpPacketReceivedEvent OnTcpPacketReveived;

    DECLARE_EVENT(UdpPacketReceivedEvent, sf::Packet&, sf::IpAddress, unsigned short);
    UdpPacketReceivedEvent OnUdpPacketReveived;

protected:
    // This function checks the status of the TCP listener socket and
    // accept any incomming connection.
    void HandleIncomingConnection();

    // Function to handle the reception of TCP packets.
    // It evokes ProcessTcpPacket upon packet received.
    void ReceiveTcpPacket(sf::TcpSocket* socket);

    // Function to handle the reception of UDP packets.
    // It evokes ProcessUdpPacket upon packet received.
    void ReceiveUdpPacket();

    // Send a TCP packet to the specified TCP socket.
    void SendTcpPacket(sf::Packet &packet, sf::TcpSocket* socket);

    // Send a UDP packet to the specified UDP socket.
    void SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort);

    // Serialize higher-level data into a SFML Packet for transmission.
    virtual sf::Packet SerializeData(const std::any& data) const { return sf::Packet(); }

    // Deserialize an SFML Packet into higher-level data.
    virtual std::any DeserializeData(const sf::Packet& packet) const { return std::any(); }

private:
    INetwork(const INetwork&) = delete;
    INetwork(INetwork &&) = delete;
    INetwork& operator=(const INetwork&) = delete;
    INetwork&& operator=(INetwork&&) = delete;

protected:
    sf::TcpSocket m_tcpSocket;
    sf::UdpSocket m_udpSocket;
    sf::TcpListener m_listener;

private:

};