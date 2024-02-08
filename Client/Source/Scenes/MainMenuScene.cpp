#include "MainMenuScene.h"

#include "Config.h"

MainMenuScene::MainMenuScene(sf::RenderWindow& window)
    : m_window(window)
{
    m_network.Start(sf::IpAddress::LocalHost, 29029);

    // Systems
    AddSystem<InputSystem>(GetRegistry());
    AddSystem<PhysicsSystem>(GetRegistry(), m_network);
    AddSystem<RenderSystem>(GetRegistry());

    // Entities
    auto enemy = GetRegistry().create();

    auto& transform = GetRegistry().emplace<TransformComponent>(enemy);
    transform.position = sf::Vector2f(
        Constants::WINDOW_WIDTH / 2.f,
        Constants::WINDOW_HEIGHT / 2.f
    );

    auto& physics = GetRegistry().emplace<PhysicsComponent>(enemy);
    physics.maxSpeed = 125.f;

    SpriteComponent& spriteComponent = GetRegistry().emplace<SpriteComponent>(enemy);
    sf::Texture texture;
    std::string path = GetResourceDir() + "Textures/enemy.png";
    texture.loadFromFile(path);
    spriteComponent.sprite.setTexture(texture);
    auto localBounds = spriteComponent.sprite.getLocalBounds();
    spriteComponent.sprite.setOrigin(localBounds.width / 2.f, localBounds.height / 2.f);

    auto& input = GetRegistry().emplace<InputComponent>(enemy);
    input.AddAxisBinding(InputAxis::Horizontal, sf::Keyboard::D, sf::Keyboard::A);
    input.AddAxisBinding(InputAxis::Horizontal, 0, (sf::Joystick::Axis)ControllerAxis::LStickH);
    input.AddAxisBinding(InputAxis::Vertical, sf::Keyboard::S, sf::Keyboard::W);
    input.AddAxisBinding(InputAxis::Vertical, 0, (sf::Joystick::Axis)ControllerAxis::LStickV);
}

MainMenuScene::~MainMenuScene()
{
    m_network.Stop();
}
