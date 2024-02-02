#include "INetwork.h"

bool INetwork::CheckSocketStatus(sf::Socket::Status status) 
{
    bool succeeded = false;

    switch (status) 
    {
        case sf::Socket::Done:
            succeeded = true;
            break;
        case sf::Socket::NotReady:
            //std::cerr << "No data available at the moment" << std::endl;
            break;
        case sf::Socket::Partial:
            //std::cerr << "Partial data received/sent" << std::endl;
            break;
        case sf::Socket::Disconnected:
            //std::cerr << "The remote peer disconnected" << std::endl;
            break;
        case sf::Socket::Error:
            //std::cerr << "An unexpected error occurred" << std::endl;
            break;
        default:
            //std::cerr << "Unknown problem occured" << std::endl;
            break;
    }

    return succeeded;
}

void INetwork::AcceptTcpConnection()
{
    // Create a new socket for the accepted connection
    sf::TcpSocket* newTcpSocket = new sf::TcpSocket;

    if (CheckSocketStatus(m_listener.accept(*newTcpSocket)))
    {
        sf::Packet receivedPacket;
        sf::Socket::Status status = newTcpSocket->receive(receivedPacket);

        if (CheckSocketStatus(status) && receivedPacket.getDataSize() > 0)
        {
            // Process the received packet for the new connection
            ProcessTcpPacket(receivedPacket);
        }
    }

    delete newTcpSocket;
}

void INetwork::ReceiveTcpPacket() 
{
    sf::Packet receivedPacket;

    if (CheckSocketStatus(m_tcpSocket.receive(receivedPacket))) 
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

    if (CheckSocketStatus(m_udpSocket.receive(receivedPacket, remoteAddress, remotePort))) 
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
        CheckSocketStatus(status);
    }
}

void INetwork::SendUdpPacket(sf::Packet &packet, sf::IpAddress remoteAddress, unsigned short remotePort) 
{
    if(packet.getDataSize() > 0)
    {
        sf::Socket::Status status = m_udpSocket.send(packet, remoteAddress, remotePort);
        CheckSocketStatus(status);
    }
}
