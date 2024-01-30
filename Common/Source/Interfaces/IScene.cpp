#include "IScene.h"

void IScene::Update(float deltaTime)
{
    for(const auto& system : m_systems) {
        system->Update(deltaTime);
    }
}

void IScene::FixedUpdate(float deltaTime)
{
    for(const auto& system : m_systems) {
        system->FixedUpdate(deltaTime);
    }
}

void IScene::Render(sf::RenderWindow& window)
{
    for(const auto& system : m_systems) {
        system->Render(window);
    }
}

entt::registry& IScene::GetRegistry()
{
    return m_registry;
}
