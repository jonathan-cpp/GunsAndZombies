#include "EventSystem.h"

EventDispatcher& EventDispatcher::GetInstance()
{
    static EventDispatcher instance;
    return instance;
}

void EventDispatcher::AddEventListener(IEventListener* listener)
{
    if (std::find(m_eventListeners.begin(), m_eventListeners.end(), listener) == m_eventListeners.end()) 
    {
        m_eventListeners.push_back(listener);
    }
}

void EventDispatcher::RemoveEventListener(IEventListener* listener)
{
    m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end());
}

void EventDispatcher::DispatchEvent(const IEvent& event)
{
    for (auto& listener : m_eventListeners)
    {
        listener->HandleEvent(event);
    }   
}