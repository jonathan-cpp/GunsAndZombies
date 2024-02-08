#include "Client.h"

#include "Constants.h"
#include "MainMenuScene.h"
#include "LobbyScene.h"
#include "GameScene.h"

Client::Client()
{
    m_window.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT)
                    , Constants::WINDOW_TITLE
                    , sf::Style::Titlebar);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_window.setPosition(sf::Vector2i(
                        (desktop.width - Constants::WINDOW_WIDTH) / 2,
                        (desktop.height - Constants::WINDOW_HEIGHT) / 2));
	
	sf::View view(sf::FloatRect(0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    view.setCenter(Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 2.f);

	m_window.setView(view);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_window.setMouseCursorGrabbed(false);

    m_sceneManager.RegisterScene<MainMenuScene>("MainMenuScene", m_window);
    m_sceneManager.RegisterScene<LobbyScene>("LobbyScene", m_window);
    m_sceneManager.RegisterScene<GameScene>("GameScene", m_window);
    m_sceneManager.PushScene("MainMenuScene");
}

Client::~Client()
{

}

void Client::Start()
{
    sf::Clock clock;
    const sf::Time fixedTimeStep = Constants::TIME_PER_FRAME;
    sf::Time accumulator = sf::Time::Zero;

	while (m_window.isOpen()) 
    {
        sf::Time deltaTime = clock.restart();
        accumulator += deltaTime;

        sf::Event event;
        while (m_window.pollEvent(event)) 
        {
            // HandleInput
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)) 
            {
                m_window.close();
            }       
        }
        
        while (accumulator >= Constants::TIME_PER_FRAME) 
        {
            m_sceneManager.FixedUpdateScene(fixedTimeStep.asSeconds());
            accumulator -= fixedTimeStep;
        }
        
        // Update
        m_sceneManager.UpdateScene(deltaTime.asSeconds());

        m_window.clear(Constants::CANVAS_COLOR);

        // Render
        m_sceneManager.RenderScene(m_window);

        m_window.display();
    }
}
