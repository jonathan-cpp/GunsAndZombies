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

    // Event triggered when a peer has been validated after connecting.
    // Parameters:
    //   - sf::TcpSocket*: The TCP socket of the validated peer.
    //   - sf::IpAddress: The IP address of the validated peer.
    //   - unsigned short: The port number of the validated peer.
    DECLARE_EVENT(PeerValidatedEvent, sf::TcpSocket*, sf::IpAddress, unsigned short);
    PeerValidatedEvent OnPeerValidated;

protected:
    // Event triggered when a new peer successfully connects.
    // Parameters:
    //   - sf::TcpSocket*: The TCP socket of the newly connected peer.
    DECLARE_EVENT(PeerConnectedEvent, sf::TcpSocket*);
    PeerConnectedEvent OnPeerConnected;

    // Event triggered when a peer disconnects.
    // Parameters:
    //   - sf::TcpSocket*: The TCP socket of the disconnected peer.
    DECLARE_EVENT(PeerDisconnectedEvent, sf::TcpSocket*);
    PeerDisconnectedEvent OnPeerDisconnected;

    // Event triggered when a TCP packet is received from a peer.
    // Parameters:
    //   - sf::Packet&: The received TCP packet.
    DECLARE_EVENT(TcpPacketReceivedEvent, sf::Packet&);
    TcpPacketReceivedEvent OnTcpPacketReveived;

    // Event triggered when a UDP packet is received from a peer.
    // Parameters:
    //   - sf::Packet&: The received UDP packet.
    //   - sf::IpAddress: The IP address of the sender.
    //   - unsigned short: The port number of the sender.
    DECLARE_EVENT(UdpPacketReceivedEvent, sf::Packet&, sf::IpAddress, unsigned short);
    UdpPacketReceivedEvent OnUdpPacketReveived;

    // Function checks the status of the TCP listener
    // and accepts any incoming connection.
    void HandleIncomingConnection();

    // Function to handle the reception of TCP packets.
    // Parameters:
    //   - socket: Pointer to the TCP socket for which the packet is received.
    void ReceiveTcpPacket(sf::TcpSocket* socket);

    // Function to handle the reception of UDP packets.
    void ReceiveUdpPacket();

    // Send a TCP packet to the specified TCP socket.
    // Parameters:
    //   - packet: Reference to the SFML packet to be sent.
    //   - socket: Pointer to the TCP socket to which the packet is sent.
    void SendTcpPacket(sf::Packet &packet, sf::TcpSocket* socket);

    // Send a UDP packet to the specified UDP socket.
    // Parameters:
    //   - packet: Reference to the SFML packet to be sent.
    //   - remoteAddress: IP address of the remote host to which the packet is sent.
    //   - remotePort: Port number of the remote host to which the packet is sent.
    void SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort);

    // Serialize higher-level data into an SFML Packet for transmission.
    // Parameters:
    //   - const std::any& data: The data to be serialized.
    // Returns:
    //   - sf::Packet: The serialized data in an SFML Packet.
    virtual sf::Packet SerializeData(const std::any& data) const { return sf::Packet(); }

    // Deserialize an SFML Packet into higher-level data.
    // Parameters:
    //   - const sf::Packet& packet: The SFML Packet to be deserialized.
    // Returns:
    //   - std::any: The deserialized data.
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