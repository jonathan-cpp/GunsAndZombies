#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(entt::registry &registry)
    : ISystem(registry)
{
}

void PhysicsSystem::Update(float deltaTime)
{
    const float LERP_FACTOR = 1.0f - std::exp(-deltaTime * 5.f);

    // Players
    GetRegistry().view<TransformComponent, InputComponent, PhysicsComponent>().each(
        [&](TransformComponent& transform, InputComponent& input, PhysicsComponent& physics)
        {
            sf::Vector2f inputDirection(input.axisValues[InputAxis::Horizontal],
                                        input.axisValues[InputAxis::Vertical]);

            sf::Vector2f targetVelocity = normalize(inputDirection) * physics.maxSpeed;

            physics.velocity = lerp<sf::Vector2f>(physics.velocity, targetVelocity, LERP_FACTOR);

            transform.position += physics.velocity * deltaTime;
        });
}

void PhysicsSystem::FixedUpdate(float deltaTime)
{

}
