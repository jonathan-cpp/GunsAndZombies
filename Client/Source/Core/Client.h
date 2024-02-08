#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "ClientNetwork.h"
#include "Core.h"
#include "SceneManager.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class Client {
public:
    explicit Client();
    virtual ~Client();

    void Start();

private:
    Client(const Client&) = delete;
    Client(Client &&) = delete;
    Client& operator=(const Client&) = delete;
    Client&& operator=(Client&&) = delete;

private:
    // Private Functions

private:
    sf::RenderWindow m_window;
    SceneManager m_sceneManager;
};