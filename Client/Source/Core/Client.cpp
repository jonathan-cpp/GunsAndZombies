#include "Client.h"

Client::Client()
{
    m_network = std::make_shared<ClientNetwork>();
    m_network->Start(sf::IpAddress::LocalHost, 29029);
    m_network->Update(1.f);
}

Client::~Client()
{
    m_network->Stop();
}
