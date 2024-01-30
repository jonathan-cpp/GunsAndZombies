#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Thirdparty Headers
//////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include <entt/entt.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "Utility.h"

#include "Components.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class ISystem {
public:
    ISystem(entt::registry& registry) : m_registry(registry) {}
    virtual ~ISystem() = default;

	virtual void Update(float deltaTime) = 0;

    virtual void FixedUpdate(float deltaTime) {}

    virtual void Render(sf::RenderWindow& window) {};

    entt::registry& GetRegistry() { return m_registry; }

private:
    entt::registry& m_registry;
};