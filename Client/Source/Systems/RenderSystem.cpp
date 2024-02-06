#include "RenderSystem.h"

RenderSystem::RenderSystem(entt::registry& registry)
    : ISystem(registry)
{
}

void RenderSystem::Update(float deltaTime)
{
    GetRegistry().view<TransformComponent, SpriteComponent>().each(
        [&](TransformComponent& transform, SpriteComponent& spriteComponent)
        {
            spriteComponent.sprite.setPosition(transform.position);
            spriteComponent.sprite.setRotation(transform.rotation);
            spriteComponent.sprite.setScale(transform.scale);
        });

    GetRegistry().sort<SpriteComponent>(
        [](const auto& lhs, const auto& rhs) {
            const sf::FloatRect leftBounds = lhs.sprite.getGlobalBounds();
            const sf::FloatRect rightBounds = rhs.sprite.getGlobalBounds();         
            return leftBounds.top + leftBounds.height < rightBounds.top + rightBounds.height;
        });
}

void RenderSystem::Render(sf::RenderWindow& window)
{
    GetRegistry().view<SpriteComponent>().each(
        [&](const SpriteComponent& spriteComponent)
        {
            window.draw(spriteComponent.sprite);
        });
}