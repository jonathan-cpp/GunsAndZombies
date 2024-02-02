#include "ClientNetwork.h"

void ClientNetwork::Start(const sf::IpAddress &serverIp, unsigned short serverPort)
{
    // TCP connection
    CheckSocketStatus(m_tcpSocket.connect(serverIp, serverPort));

    // UDP connection
    if(CheckSocketStatus(m_udpSocket.bind(sf::Socket::AnyPort)))
    {
        // Send an initial UDP packet to the server to establish a connection
        sf::Packet packet;
        packet << "UDP packet";
        SendUdpPacket(packet, serverIp, serverPort);
        packet.clear();
        
        packet << "TCP packet";
        SendTcpPacket(packet, &m_tcpSocket);
        packet.clear();
    }
}

void ClientNetwork::Stop()
{
    // Close TCP connection
    if (m_tcpSocket.getLocalPort() != 0) 
    {
        m_tcpSocket.disconnect();
    }   

    // Close UDP connection
    if (m_udpSocket.getLocalPort() != 0) 
    {
        m_udpSocket.unbind();
    }
}

void ClientNetwork::Update(float deltaTime)
{
}
