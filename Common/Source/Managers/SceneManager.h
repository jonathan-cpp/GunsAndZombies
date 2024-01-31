#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <unordered_map>
#include <stack>
#include <memory>
#include <string>
#include <iostream>

//////////////////////////////////////////////////////////
// Thirdparty Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "IScene.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class SceneManager {
public:
    SceneManager();
    virtual ~SceneManager() = default;

    template <typename T>
    void RegisterScene(const std::string& id, sf::RenderWindow& m_window);
    
    void PushScene(const std::string& id);
    void PopScene();
    void ClearSceneStack();

    IScene* GetCurrentScene() const;

    void UpdateScene(float deltaTime);
    void FixedUpdateScene(float deltaTime);
    void RenderScene(sf::RenderWindow& window);

private:
    std::unordered_map<std::string, std::unique_ptr<IScene>> m_scenes;
    std::stack<IScene*> m_sceneStack;
};

template <typename T>
inline void  SceneManager::RegisterScene(const std::string& id, sf::RenderWindow& m_window) {
    if (m_scenes.find(id) != m_scenes.end()) {
        std::cerr << "Scene with the same ID already exists: " + id << std::endl;
    }
    
    m_scenes[id] = std::make_unique<T>(m_window);
}