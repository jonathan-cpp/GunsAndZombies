#include "Client.h"

#include "GamePlayScene.h"

Client::Client() 
{
    
    m_network->StartNetworkThread("localhost", 29027);

    const int width = 800;
    const int height = 600;

    m_window.create(sf::VideoMode(width, height), "[ Guns & Zombies ]", sf::Style::Default);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    m_window.setPosition(sf::Vector2i((desktop.width - width) / 2, (desktop.height - height) / 2));

    sf::View view(sf::FloatRect(0, 0, width, height));
    m_window.setView(view);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_window.setMouseCursorGrabbed(false);

    m_sceneManager.RegisterScene<GamePlayScene>("GamePlayScene", m_window);
    m_sceneManager.PushScene("GamePlayScene");
}

void Client::Run() 
{
    sf::Clock clock;
    const sf::Time fixedTimeStep = sf::seconds(1.0f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    while (m_window.isOpen()) 
    {
        // Handle events
        sf::Event event;
        while (m_window.pollEvent(event)) 
        {
            handleEvent(event);
        }

        // Calculate delta time
        sf::Time deltaTime = clock.restart();
        accumulator += deltaTime;

        // Fixed time step update
        while (accumulator >= fixedTimeStep) 
        {
            m_sceneManager.FixedUpdateScene(deltaTime.asSeconds());
            accumulator -= fixedTimeStep;
        }

        // Variable time step update
        m_sceneManager.UpdateScene(deltaTime.asSeconds());

        // Rendering
        m_window.clear();

        m_sceneManager.RenderScene(m_window);

        m_window.display();
    }
}

void Client::handleEvent(const sf::Event& event) 
{
    switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                m_window.close();
            }
            // Handle other key events if needed
            break;
        // Handle other event types if needed
    }
}

