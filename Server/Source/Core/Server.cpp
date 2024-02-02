#include "Server.h"

Server::Server()
{
    m_network = std::make_shared<ServerNetwork>();
    m_network->Start(sf::IpAddress::LocalHost, 29029);
    m_network->Update(0.16f);
}

Server::~Server()
{
    m_network->Stop();
}
