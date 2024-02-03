#include "ServerNetwork.h"

void ServerNetwork::Start(const sf::IpAddress &serverIp, unsigned short serverPort)
{
    // Create and bind the TCP listener
    if(m_listener.listen(serverPort, serverIp) == sf::Socket::Done)
    {
        m_listener.setBlocking(false);
        std::cout << "Server TCP started on IP: " << serverIp.toString() << ", Port: " << serverPort << std::endl;
    }

    if (m_udpSocket.bind(serverPort, serverIp) == sf::Socket::Done) 
    {
        m_udpSocket.setBlocking(false);
        std::cout << "Server UDP started on IP: " << serverIp.toString() << ", Port: " << serverPort << std::endl;
    }

    OnPeerConnected += [this](sf::TcpSocket* socket) {
        ClientData clientData;
        clientData.tcpSocket = std::shared_ptr<sf::TcpSocket>(socket);
        m_connectedClients.push_back(clientData);
        m_selector.add(*clientData.tcpSocket);
        
        sf::Packet packet;
        packet << "Welcome to the server!";
        SendTcpPacket(packet, socket);
        packet.clear();
    };

    OnTcpPacketReveived += [](sf::Packet& packet) {
        std::string msg;
        packet >> msg;
        std::cout << msg << std::endl;
    };

    OnUdpPacketReveived += [](sf::Packet& packet, sf::IpAddress ipAdress, unsigned int port) {
        std::string msg;
        packet >> msg;
        std::cout << msg << std::endl;
    };

    m_tcpThread = std::thread(&ServerNetwork::HandleTcpConnectionsThread, this);
}

void ServerNetwork::Stop()
{
    // Close the TCP listener
    m_listener.close();

    // Unbind the UDP socket
    m_udpSocket.unbind();

    if (m_tcpThread.joinable())
    {
        m_tcpThread.join();
    }
}

void ServerNetwork::Update(float deltaTime)
{
    sf::Clock clock;

    while(clock.getElapsedTime().asSeconds() < 5.f) 
    {
        ReceiveUdpPacket();

        // Use the selector to check which sockets are ready
        if (m_selector.wait(sf::milliseconds(100))) 
        {
            for (auto& clientData : m_connectedClients) 
            {
                if (m_selector.isReady(*clientData.tcpSocket)) {
                    ReceiveTcpPacket(clientData.tcpSocket.get());
                }
            }
        }
    
        //Prediction(deltaTime);

        //SyncPlayers(deltaTime);

        DisconnectPlayers();        
    }
}

void ServerNetwork::HandleTcpConnectionsThread()
{
    while (true)
    {
        HandleIncomingConnection();
    }
}

void ServerNetwork::DisconnectPlayers()
{
    for (auto& client : m_connectedClients)
    {
        
    }
}

void ServerNetwork::Broadcast(sf::Packet &packet, const sf::IpAddress& ignore)
{
    for (auto& client : m_connectedClients)
    {
        if(client.address != ignore)
        {
            SendTcpPacket(packet, client.tcpSocket.get());
        }
    }
}
