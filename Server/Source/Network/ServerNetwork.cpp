#include "ServerNetwork.h"

void ServerNetwork::Start(const sf::IpAddress &serverIp, unsigned short serverPort)
{
    // Create and bind the TCP listener
    if(CheckSocketStatus(m_listener.listen(serverPort, serverIp)))
    {
        m_listener.setBlocking(false);
        std::cout << "Server TCP started on IP: " << serverIp.toString() << ", Port: " << serverPort << std::endl;
    }

    if (CheckSocketStatus(m_udpSocket.bind(serverPort, serverIp))) 
    {
        m_udpSocket.setBlocking(false);
        std::cout << "Server UDP started on IP: " << serverIp.toString() << ", Port: " << serverPort << std::endl;
    }

    m_tcpThread = std::thread(&ServerNetwork::handleTcpConnectionsThread, this);
}

void ServerNetwork::Stop()
{
    // Close the TCP listener
    m_listener.close();

    // Unbind the UDP socket
    m_udpSocket.unbind();

    if (m_tcpThread.joinable())
        m_tcpThread.join();
}

void ServerNetwork::Update(float deltaTime)
{
    while(true)
    {
        ReceiveUdpPacket();
    }
}

void ServerNetwork::handleTcpConnectionsThread()
{
    while (true)
    {
        AcceptTcpConnection();
    }
}

void ServerNetwork::ProcessTcpPacket(const sf::Packet &receivedPacket)
{
    std::cout << "TCP packet received!" << std::endl;
}

void ServerNetwork::ProcessUdpPacket(const sf::Packet &receivedPacket, sf::IpAddress remoteAddress, unsigned short remotePort)
{
    std::cout << "UDP packet received!" << std::endl;
}
