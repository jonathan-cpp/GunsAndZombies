#include "Server.h"

Server::Server() 
{
    logl("Server::Server()");
    m_network = std::make_unique<ServerNetwork>();
    m_network->StartNetworkThread("localhost", 29027);
}

void Server::Run() 
{
    logl("Server::Run()");

    sf::Clock clock;
    const sf::Time fixedTimeStep = sf::seconds(1.0f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    while (true) 
    {
        m_network->NetworkThreadFunction();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}
