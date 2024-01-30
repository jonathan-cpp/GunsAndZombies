#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
}

ServerNetwork::~ServerNetwork()
{
    m_exitThread = true;
    if (m_networkThread.joinable())
    {
        m_networkThread.join();
    }
}

void ServerNetwork::StartNetworkThread(sf::IpAddress ip, uint16_t port)
{
    logl("ServerNetwork::StartNetworkThread()");
    m_exitThread = !(m_listener.listen(port) == sf::Socket::Status::Done);
    m_networkThread = std::thread(&ServerNetwork::ConnectClients, this);
}

void ServerNetwork::ConnectClients()
{
    while (true)
    {
        auto new_client = new sf::TcpSocket();
        if (m_listener.accept(*new_client) == sf::Socket::Done)
        {
            new_client->setBlocking(false);
            m_clients.push_back(std::move(new_client));
            logl("Added client " << m_clients.back()->getRemoteAddress() << ":" << m_clients.back()->getRemotePort() << " on slot " << m_clients.size());
        }
        else
        {
            logl("Server listener error, restart the server");
            delete new_client;
            break;
        }
    }
}

void ServerNetwork::DisconnectClient(sf::TcpSocket *socket_pointer, size_t position)
{
    auto& client = m_clients[position];
    logl("Client " << client->getRemoteAddress() << ":" << client->getRemotePort() << " disconnected, removing");
    client->disconnect();
    m_clients.erase(m_clients.begin() + position);
}

void ServerNetwork::BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port)
{
    for (size_t iterator = 0; iterator < m_clients.size(); iterator++)
    {
        auto& client = m_clients[iterator];
        if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port)
        {
            if (client->send(packet) != sf::Socket::Done)
            {
                logl("Could not send packet on broadcast");
            }
        }
    }
}

void ServerNetwork::ReceivePacket(sf::TcpSocket *client, size_t iterator)
{
    sf::Packet packet;

    switch (client->receive(packet))
    {
        case sf::Socket::Done:
            if (packet.getDataSize() > 0)
            {
                std::string received_message;
                packet >> received_message;
                packet.clear();

                packet << received_message << client->getRemoteAddress().toString() << client->getRemotePort();

                BroadcastPacket(packet, client->getRemoteAddress(), client->getRemotePort());
                logl(client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " '" << received_message << "'");   
            }
            break;

        case sf::Socket::NotReady:
            // No data available, handle accordingly
            break;

        case sf::Socket::Disconnected:
            DisconnectClient(client, iterator);
            break;

        default:
            // Handle other socket errors
            break;
    }
}

void ServerNetwork::NetworkThreadFunction()
{
    while (true)
    {
        for (size_t iterator = 0; iterator < m_clients.size(); iterator++)
        {
            ReceivePacket(m_clients[iterator], iterator);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }  
}
