#include "INetwork.h"

bool INetwork::CheckSocketStatus(sf::Socket::Status status) 
{
    bool succeeded = false;

    switch (status) 
    {
        case sf::Socket::Done:
            // Operation succeeded
            succeeded = true;
            break;
        case sf::Socket::NotReady:
            // No data available at the moment
            break;
        case sf::Socket::Partial:
            // Partial data received/sent
            break;
        case sf::Socket::Disconnected:
            // The remote peer disconnected
            break;
        case sf::Socket::Error:
            // An unexpected error occurred
            break;
        default:
            // Handle any other status that might be added in the future
            break;
    }

    return succeeded;
}

void INetwork::ReceiveTcpPacket() 
{
    sf::Packet receivedPacket;
    sf::Socket::Status status = m_tcpSocket->receive(receivedPacket);

    if (CheckSocketStatus(status)) 
    {
        if(receivedPacket.getDataSize() > 0)
        {     
            ProcessTcpPacket(receivedPacket);
        }
    }   
}   

void INetwork::ReceiveUdpPacket() 
{
    sf::Packet receivedPacket;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;

    sf::Socket::Status status = m_udpSocket->receive(receivedPacket, remoteAddress, remotePort);

    if (CheckSocketStatus(status)) 
    {
        if(receivedPacket.getDataSize() > 0)
        {     
            ProcessUdpPacket(receivedPacket, remoteAddress, remotePort);
        }
    }  
}

void INetwork::SendTcpPacket(sf::Packet &packet, std::shared_ptr<sf::TcpSocket> socket) 
{
    if(packet.getDataSize() > 0)
    {
        sf::Socket::Status status = socket->send(packet);
        CheckSocketStatus(status);
    }
}

void INetwork::SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort) 
{
    if(packet.getDataSize() > 0)
    {
        sf::Socket::Status status = m_udpSocket->send(packet, remoteAddress, remotePort);
        CheckSocketStatus(status);
    }
}
