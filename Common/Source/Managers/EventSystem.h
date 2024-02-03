#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <memory>

//////////////////////////////////////////////////////////
// External Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Constants and Enums
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

template <typename... TArgs>
class BaseEvent {
public:
    using EventCallback = std::function<void(TArgs...)>;

    void operator+=(EventCallback func) {
        m_subsribers.emplace_back(func);
    }

    void operator()(TArgs... args) {
        for (const auto& subscriber : m_subsribers) {
            subscriber(args...);
        }
    }

private:
    std::vector<EventCallback> m_subsribers;
};

#define DECLARE_EVENT(eventName, ...) \
class eventName : public BaseEvent<__VA_ARGS__> {};

//
// How to use
//
//class ExampleClass {
//public:
//    DECLARE_EVENT(ExampleEvent, float, float)
//    // or using ExampleEvent = BaseEvent<float, float>;
//    ExampleEvent OnExampleEvent;
//};

class IEvent {
public:
    virtual ~IEvent() = default;
};

class IEventListener {
public:
    virtual ~IEventListener() = default;
    virtual bool HandleEvent(const IEvent& event) = 0;
};

class EventDispatcher {
public:  
    static EventDispatcher& GetInstance() {
        static EventDispatcher instance; 
        return instance;
    }

    template <typename EventType>
    void AddEventListener(std::shared_ptr<IEventListener> listener) {
        auto& listeners = m_eventListeners[typeid(EventType)];
        auto it = std::find(listeners.begin(), listeners.end(), listener);
        if (it == listeners.end()) { 
            listeners.emplace_back(std::move(listener)); 
        }
    }

    template <typename EventType>
    void RemoveEventListener(std::shared_ptr<IEventListener> listener) {
        auto& listeners = m_eventListeners[typeid(EventType)];
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

    template <typename EventType>
    void DispatchEvent(const EventType& event) {
        const auto& listeners = m_eventListeners[typeid(EventType)];
        for (auto& listener : listeners) {
            listener->HandleEvent(event);
        }
    }

private:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;

private:
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<IEventListener>>> m_eventListeners;
};
