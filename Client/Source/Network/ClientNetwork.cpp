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

    OnTcpPacketReveived += [](sf::Packet& packet) {
        std::string msg;
        packet >> msg;
        std::cout << msg << std::endl;
    };

    OnUdpPacketReveived += [](sf::Packet& packet, sf::IpAddress ipAdress, unsigned int port) {
        std::string msg;
        packet >> msg;
        std::cout << msg << std::endl;
    };
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
    sf::Clock clock;

    while(clock.getElapsedTime().asSeconds() < 5.f) 
    {
        ReceiveTcpPacket(&m_tcpSocket);
    }
}
