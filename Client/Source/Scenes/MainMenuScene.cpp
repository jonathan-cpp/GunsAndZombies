#include "MainMenuScene.h"

#include "Config.h"

MainMenuScene::MainMenuScene(sf::RenderWindow& window)
    : m_window(window)
{
    // Systems
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
}