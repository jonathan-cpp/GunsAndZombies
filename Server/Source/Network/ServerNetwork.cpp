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
    };

    OnTcpPacketReveived += [this](sf::Packet& packet) { HandlePacket(packet); };
    OnUdpPacketReveived += [this](sf::Packet& packet, sf::IpAddress ip, unsigned short port) { HandlePacket(packet, ip, port); };

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

    if (m_udpThread.joinable())
    {
        m_udpThread.join();
    }
}

void ServerNetwork::Update(float deltaTime)
{
    sf::Clock clock;

    while(true) 
    {
        ReceiveUdpPacket();

        // Use the selector to check which sockets are ready
        if (m_selector.wait(sf::milliseconds(10))) 
        {
            for (auto& clientData : m_connectedClients) 
            {
                if (m_selector.isReady(*clientData.tcpSocket)) 
                {
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

void ServerNetwork::HandlePacket(sf::Packet &packet)
{

}

void ServerNetwork::HandlePacket(sf::Packet &packet, sf::IpAddress ip, unsigned short port)
{
    float x, y;
    std::uint32_t entity;
    packet >> entity >> x >> y;
}
