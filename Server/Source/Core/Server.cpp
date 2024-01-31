#include "Server.h"

Server::Server() 
{
    logl("Server::Server()");
    m_network = std::make_unique<NetworkManager>();
    m_network->StartServer(12345);
}

void Server::Run() 
{
    logl("Server::Run()");

    sf::Clock clock;
    const sf::Time fixedTimeStep = sf::seconds(1.0f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}
