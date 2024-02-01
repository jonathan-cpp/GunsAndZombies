#include "EntryPoint.h"

class NewEvent : public IEvent {
public:
    NewEvent(std::size_t s) : size(s) {}
    
    std::size_t size;
};

class NewListener : public IEventListener {
public:
    bool HandleEvent(const IEvent& event) override {
        if (auto newEvent = dynamic_cast<const NewEvent*>(&event)) {
            std::cout << "NewEvent detected with size: " << newEvent->size << std::endl;
            return true;  // Event handled successfully
        }
        return false;  // Event not handled
    }
};


class Allocator {
public:
    void Allocate(size_t size) { 
        EventDispatcher::GetInstance().DispatchEvent(NewEvent(size));
        OnAllocate(size);
    }

    using Event = BaseEvent<size_t>;
    Event OnAllocate;

};

int main() 
{
    NewListener newListener;
    EventDispatcher::GetInstance().AddEventListener(&newListener);

    // Trigger events   
    Allocator allocator;
    allocator.OnAllocate += [&](size_t size) {
        std::cout << "Allocator allocated size: " << size << std::endl;
    };

    allocator.Allocate(1337);

    return 0;
}
