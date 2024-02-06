#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <memory>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////

#include <entt/entt.hpp>

//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "Systems.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

class IScene {
public:
    explicit IScene() = default;
    virtual ~IScene() = default;

    void IScene::Update(float deltaTime) {
        for(const auto& system : m_systems) {
            system->Update(deltaTime);
        }
    }

    void IScene::FixedUpdate(float deltaTime) {
        for(const auto& system : m_systems) {
            system->FixedUpdate(deltaTime);
        }
    }

    void IScene::Render(sf::RenderWindow& window) {
        for(const auto& system : m_systems) {
            system->Render(window);
        }
    }

    template<typename T, typename... Args>
    T* AddSystem(Args&&... args);

private:
    IScene(const IScene&) = delete;
    IScene(IScene &&) = delete;
    IScene& operator=(const IScene&) = delete;
    IScene&& operator=(IScene&&) = delete;

protected:
    entt::registry& GetRegistry() { return m_registry; }
    
private:
    entt::registry m_registry;

    std::vector<std::unique_ptr<ISystem>> m_systems;
};

template <typename T, typename... Args>
inline T* IScene::AddSystem(Args&&... args) {
    T* ptr = new T(std::forward<Args>(args)...);
    m_systems.emplace_back(ptr);
    return ptr;
}