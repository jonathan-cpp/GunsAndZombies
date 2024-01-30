#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Thirdparty Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "ISystem.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class RenderSystem : public ISystem {
public:
    RenderSystem(entt::registry& registry);

	virtual void Update(float deltaTime) override;

    virtual void Render(sf::RenderWindow& window) override;

private:

};