#include "NetworkManager.h"

NetworkManager::NetworkManager() 
    : m_exitThread(false) 
{
}

NetworkManager::~NetworkManager() 
{
    m_exitThread = true;

    if (m_networkThread.joinable()) {
        m_networkThread.join();
    }

    StopClient();
    StopServer();
}

void NetworkManager::StartClient(const sf::IpAddress& serverIp, uint16_t serverPort) 
{
    StopClient();

    m_clientSocket.setBlocking(true);

    if(m_clientSocket.connect(serverIp, serverPort) != sf::Socket::Status::Done)
    {
        logl("Failed to connect to the server");
        return;
    }

    m_networkThread = std::thread(&NetworkManager::ClientThread, this);
}

void NetworkManager::StopClient() 
{
    if (m_clientSocket.getRemoteAddress() != sf::IpAddress::None) 
    {
        m_clientSocket.disconnect();
    }
}

void NetworkManager::ClientThread()
{
    while (!m_exitThread) 
    {
        // Common logic for the client
        ReceivePacket(m_clientSocket, 0);  // Assuming only one client for simplicity

        // Optionally, you can add additional client-specific logic here

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void NetworkManager::StartServer(uint16_t port) 
{
    StopServer();

    if (m_serverListener.listen(port) != sf::Socket::Done) 
    {
        logl("Failed to start the server on port " << port);
        return;
    }

    m_networkThread = std::thread(&NetworkManager::HandleClientConnections, this);
}

void NetworkManager::StopServer() 
{
    m_serverListener.close();

    for (auto& client : m_clients) 
    {
        client->disconnect();
    }

    m_clients.clear();
}

void NetworkManager::HandleClientConnections() 
{
    while (!m_exitThread) 
    {
        // Server logic: Accept incoming connections if there are clients  
        auto newClient = std::make_unique<sf::TcpSocket>();
        if (m_serverListener.accept(*newClient) == sf::Socket::Done) 
        {
            newClient->setBlocking(false);
            m_clients.emplace_back(std::move(newClient));
            logl("Client connected: " << m_clients.back()->getRemoteAddress() << ":" << m_clients.back()->getRemotePort() << " on slot " << m_clients.size());

            // Send a welcome message to the connected client
            sf::String msg("Hi, you've connected to the server!");
            sf::Packet packet;
            packet << msg;

            // Send the entire packet
            sf::Socket::Status sendStatus = m_clients.back()->send(packet);

            if (sendStatus == sf::Socket::Partial || sendStatus == sf::Socket::NotReady)
            {
                logl("Welcome message partially sent or not sent at all, handle accordingly");
            }
            else if (sendStatus == sf::Socket::Error)
            {
                logl("An error occurred during the send operation, handle accordingly");
            }
            else if (sendStatus == sf::Socket::Done)
            {
                logl("Welcome message sent successfully");
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void NetworkManager::HandleClientPackets() 
{
    while (!m_exitThread) 
    {
        for (size_t iterator = 0; iterator < m_clients.size(); iterator++) 
        {
            ReceivePacket(*m_clients[iterator], iterator);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void NetworkManager::BroadcastPacket(sf::Packet &packet, sf::IpAddress excludeAddress, unsigned short port)
{
    for (size_t iterator = 0; iterator < m_clients.size(); iterator++)
    {
        auto& client = m_clients[iterator];
        if (client->getRemoteAddress() != excludeAddress || client->getRemotePort() != port)
        {
            if (client->send(packet) != sf::Socket::Done)
            {
                logl("Could not send packet on broadcast");
            }
        }
    }
}

void NetworkManager::ReceivePacket(sf::TcpSocket& socket, size_t clientId) 
{
    sf::Packet packet;

    switch (socket.receive(packet)) 
    {
        case sf::Socket::Done:
            if (packet.getDataSize() > 0) 
            {
                sf::String receivedMessage;
                packet >> receivedMessage;
                logl("Received from " << socket.getRemoteAddress().toString() << ":" << socket.getRemotePort() << " '" << receivedMessage.toAnsiString() << "'");
            }
            break;

        case sf::Socket::NotReady:
            // No data available, handle accordingly
            break;

        case sf::Socket::Disconnected:
            DisconnectClient(clientId);
            StopClient();
            break;

        default:
            break;
    }
}

void NetworkManager::SendPacket(sf::Packet &packet, sf::TcpSocket* socket)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (packet.getDataSize() > 0 && socket->send(packet) != sf::Socket::Done) 
    {
        logl("Error sending packet.");
    }
}

void NetworkManager::DisconnectClient(size_t position)
{
    if (position < m_clients.size()) 
    {
        auto& client = m_clients[position];
        logl("Client " << client->getRemoteAddress() << ":" << client->getRemotePort() << " disconnected, removing");
        
        // Disconnect the client
        client->disconnect();

        // Remove the client from the vector
        m_clients.erase(m_clients.begin() + position);
    }
    else 
    {
        logl("Invalid client position");
    }
}