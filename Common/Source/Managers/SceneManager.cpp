#include "SceneManager.h"

SceneManager::SceneManager()
{

}

void SceneManager::PushScene(const std::string &id)
{
    auto it = m_scenes.find(id);
    if (it != m_scenes.end()) {
        m_sceneStack.push(it->second.get());
    }
}

void SceneManager::PopScene() 
{
    if (!m_sceneStack.empty()) {
        m_sceneStack.pop();
    }
}

void SceneManager::ClearSceneStack()
{
    while(!m_sceneStack.empty()) {
        m_sceneStack.pop();
    }
}

IScene *SceneManager::GetCurrentScene() const
{
    if (!m_sceneStack.empty()) {
        return m_sceneStack.top();
    }
    
    return nullptr;
}

void SceneManager::UpdateScene(float deltaTime) 
{
    if(!m_sceneStack.empty()) {
        m_sceneStack.top()->Update(deltaTime);
    }
}

void SceneManager::FixedUpdateScene(float deltaTime) 
{
    if(!m_sceneStack.empty()) {
        m_sceneStack.top()->FixedUpdate(deltaTime);
    }
}

void SceneManager::RenderScene(sf::RenderWindow& window)
{
    if(!m_sceneStack.empty()) {
        m_sceneStack.top()->Render(window);
    }
}
