#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////

#include <iostream>
#include <functional>
#include <vector>

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
//    ExampleEvent OnEvent;
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
    // Get a reference to the singleton instance of EventDispatcher
    static EventDispatcher& GetInstance();

    // Add an event listener to the dispatcher
    void AddEventListener(IEventListener* listener);

    // Remove an event listener from the dispatcher
    void RemoveEventListener(IEventListener* listener);

    // Dispatch an event to all registered listeners
    void DispatchEvent(const IEvent& event);

private:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;

private:
    std::vector<IEventListener*> m_eventListeners;
};
