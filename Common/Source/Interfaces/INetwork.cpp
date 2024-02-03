#include "INetwork.h"

void INetwork::AcceptTcpConnection()
{
    // Create a new socket for the accepted connection
    sf::TcpSocket* newTcpSocket = new sf::TcpSocket;

    sf::Socket::Status status = m_listener.accept(*newTcpSocket);

    if (status == sf::Socket::Done)
    {
        ClientConnected(newTcpSocket);
    }
    else 
    {
        delete newTcpSocket;
    }
}

void INetwork::ReceiveTcpPacket(sf::TcpSocket* socket) 
{
    sf::Packet receivedPacket;

    sf::Socket::Status status = socket->receive(receivedPacket);
    if (status == sf::Socket::Done)
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

    sf::Socket::Status status = m_udpSocket.receive(receivedPacket, remoteAddress, remotePort);
    if (status == sf::Socket::Done)
    {
        if(receivedPacket.getDataSize() > 0)
        {     
            ProcessUdpPacket(receivedPacket, remoteAddress, remotePort);
        }
    }  
}

void INetwork::SendTcpPacket(sf::Packet &packet, sf::TcpSocket* socket) 
{
    if(packet.getDataSize() > 0)
    {
        sf::Socket::Status status = socket->send(packet);
        switch (status) 
        {
            case sf::Socket::Done:
                break;
            case sf::Socket::NotReady:
                break;
            case sf::Socket::Partial:
                break;
            case sf::Socket::Disconnected:
                break;
            case sf::Socket::Error:
                break;
            default:
                break;
        }
    }
}

void INetwork::SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort) 
{
    if(packet.getDataSize() > 0)
    {
        sf::Socket::Status status = m_udpSocket.send(packet, remoteAddress, remotePort);
        switch (status) 
        {
            case sf::Socket::Done:
                break;
            case sf::Socket::NotReady:
                break;
            case sf::Socket::Partial:
                break;
            case sf::Socket::Disconnected:
                break;
            case sf::Socket::Error:
                break;
            default:
                break;
        }
    }
}
