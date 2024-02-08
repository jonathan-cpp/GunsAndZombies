#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(entt::registry &registry, ClientNetwork& network)
    : ISystem(registry)
    , m_network(network)
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
    // Player Position Network
    GetRegistry().view<TransformComponent, InputComponent, PhysicsComponent>().each(
        [&](const entt::entity entity, TransformComponent& transform, InputComponent& input, PhysicsComponent& physics)
        {
            sf::Packet packet;
            packet << (std::uint32_t)entity << transform.position.x << transform.position.y;
            m_network.SendUdpPacket(packet, sf::IpAddress::LocalHost, 29029);
        });
}
