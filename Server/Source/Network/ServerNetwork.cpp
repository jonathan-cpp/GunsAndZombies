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

    m_tcpThread = std::thread(&ServerNetwork::handleTcpConnectionsThread, this);
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
    while(true)
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

        disconnectPlayers();        
    }
}

void ServerNetwork::ClientConnected(sf::TcpSocket* socket) 
{
    ClientData clientData;
    clientData.tcpSocket = std::shared_ptr<sf::TcpSocket>(socket);
    m_connectedClients.push_back(clientData);
    m_selector.add(*clientData.tcpSocket);
}

void ServerNetwork::handleTcpConnectionsThread()
{
    while (true)
    {
        AcceptTcpConnection();
    }
}

void ServerNetwork::disconnectPlayers()
{
    for (int i = 0; i < m_connectedClients.size(); i++)
    {

    }
}

void ServerNetwork::ProcessTcpPacket(sf::Packet &receivedPacket)
{
    std::string msg;
    receivedPacket >> msg;
    std::cout << msg << std::endl;
}

void ServerNetwork::ProcessUdpPacket(sf::Packet &receivedPacket, sf::IpAddress remoteAddress, unsigned short remotePort)
{
    std::string msg;
    receivedPacket >> msg;
    std::cout << msg << std::endl;
}
