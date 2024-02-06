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

#include "IScene.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class LobbyScene : public IScene {
public:
    explicit LobbyScene(sf::RenderWindow& window);
    virtual ~LobbyScene() = default;

    // Public Functions

private:
    LobbyScene(const LobbyScene&) = delete;
    LobbyScene(LobbyScene &&) = delete;
    LobbyScene& operator=(const LobbyScene&) = delete;
    LobbyScene&& operator=(LobbyScene&&) = delete;

private:
    // Private Functions

private:
    sf::RenderWindow& m_window;
};