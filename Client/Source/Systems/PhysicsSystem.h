#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "ISystem.h"
#include "ClientNetwork.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class PhysicsSystem : public ISystem {
public:
    PhysicsSystem(entt::registry& registry, ClientNetwork& network);
    virtual ~PhysicsSystem() = default;

	virtual void Update(float deltaTime) override;

	virtual void FixedUpdate(float deltaTime) override;

private:
    PhysicsSystem(const PhysicsSystem&) = delete;
    PhysicsSystem(PhysicsSystem &&) = delete;
    PhysicsSystem& operator=(const PhysicsSystem&) = delete;
    PhysicsSystem&& operator=(PhysicsSystem&&) = delete;

private:
    // Private Functions

private:
    ClientNetwork& m_network;

};