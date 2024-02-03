#include "ClientNetwork.h"

void ClientNetwork::Start(const sf::IpAddress &serverIp, unsigned short serverPort)
{
    // TCP connection 
    if(m_tcpSocket.connect(serverIp, serverPort) != sf::Socket::Done)
    {
        return;
    }

    // UDP connection
    if(m_udpSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
        return;
    }

    sf::Packet packet;
    for (int i = 0; i < 25; i++)
    {      
        // Send an initial UDP packet to the server to establish a connection
        std::string msg = "UDP packet " + std::to_string(i);
        packet << msg;
        SendUdpPacket(packet, serverIp, serverPort);
        packet.clear();
        
        msg = "TCP packet " + std::to_string(i);
        packet << msg;
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
