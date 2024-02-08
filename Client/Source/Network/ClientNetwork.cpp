#include "ClientNetwork.h"

void ClientNetwork::Start(const sf::IpAddress &serverIp, unsigned short serverPort)
{
    // TCP connection 
    if(m_tcpSocket.connect(serverIp, serverPort) != sf::Socket::Done)
    {
        std::cout << "TCP connection failed." << std::endl;
        return;
    }

    // UDP connection
    if(m_udpSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
        std::cout << "UDP bind failed." << std::endl;
        return;
    }

    OnTcpPacketReveived += [](sf::Packet& packet) {
        float x, y;
        packet >> x >> y;
        std::cout << x << " " << y << std::endl;
    };

    OnUdpPacketReveived += [](sf::Packet& packet, sf::IpAddress ipAdress, unsigned int port) {
        float x, y;
        packet >> x >> y;
        std::cout << x << " " << y << std::endl;
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
