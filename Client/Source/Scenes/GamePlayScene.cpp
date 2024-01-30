#include "GamePlayScene.h"

#include "Config.h"

#include "RenderSystem.h"

GamePlayScene::GamePlayScene(sf::RenderWindow& window)
    : m_window(window)
{
    // Initialize and add systems in the desired order
    AddSystem<InputSystem>(GetRegistry());
    AddSystem<PhysicsSystem>(GetRegistry());
    AddSystem<RenderSystem>(GetRegistry());

    // Add Entities

    auto player = GetRegistry().create();

    auto& transform = GetRegistry().emplace<TransformComponent>(player);
    transform.position = sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

    auto& physics = GetRegistry().emplace<PhysicsComponent>(player);
    physics.maxSpeed = 125.f;

    auto& sprite = GetRegistry().emplace<SpriteComponent>(player);
    sf::Texture texture;
    texture.loadFromFile(GetResourceDir() + "Textures/player.png");
    sprite.sprite.setTexture(texture);
    sprite.sprite.setPosition(transform.position);

    auto& input = GetRegistry().emplace<InputComponent>(player);
    input.AddAxisBinding(InputAxis::Horizontal, sf::Keyboard::D, sf::Keyboard::A);
    input.AddAxisBinding(InputAxis::Horizontal, 0, (sf::Joystick::Axis)ControllerAxis::LStickH);
    input.AddAxisBinding(InputAxis::Vertical, sf::Keyboard::S, sf::Keyboard::W);
    input.AddAxisBinding(InputAxis::Vertical, 0, (sf::Joystick::Axis)ControllerAxis::LStickV);
}
