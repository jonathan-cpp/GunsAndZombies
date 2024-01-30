#include "ClientNetwork.h"

static constexpr float TIMEOUT = 10.f;

ClientNetwork::ClientNetwork()
{
    m_tcpSocket.setBlocking(false);
}

ClientNetwork::~ClientNetwork()
{
    m_exitThread = true;
    if (m_networkThread.joinable())
    {
        m_networkThread.join();
    }
}

void ClientNetwork::StartNetworkThread(sf::IpAddress ip, uint16_t port)
{
    logl("ClientNetwork::StartNetworkThread()");

    // Establish connection to the server
    if (m_tcpSocket.connect(ip, port) == sf::Socket::Done) 
    {
        m_exitThread = false;
        m_networkThread = std::thread(&ClientNetwork::ReceivePackets, this, &m_tcpSocket);
        logl("Connected to server");
    } 
    else 
    {
        logl("Connection attempt timed out");
        return;
    }
}

void ClientNetwork::ReceivePackets(sf::TcpSocket *socket)
{
     while (true)
     {
          if (socket->receive(m_lastPacket) == sf::Socket::Done)
          {
               std::string received_string;
               std::string sender_address;
               unsigned short sender_port;
               m_lastPacket >> received_string >> sender_address >> sender_port;
               logl("From (" << sender_address << ":" << sender_port << "): " << received_string);
          }

          std::this_thread::sleep_for((std::chrono::milliseconds)250);
     }
}

void ClientNetwork::SendPacket(sf::Packet &packet)
{
     if (packet.getDataSize() > 0 && m_tcpSocket.send(packet) != sf::Socket::Done)
     {
          log("Could not send packet");
     }
}

void ClientNetwork::NetworkThreadFunction()
{

}
