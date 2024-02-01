#include "EntryPoint.h"

class AllocateEvent : public IEvent {
public:
    AllocateEvent(std::size_t s) : size(s) {}
    
    std::size_t size;
};

class DeallocateEvent : public IEvent {
public:
    DeallocateEvent(std::size_t s) : size(s) {}
    
    std::size_t size;
};

class AllocateListener : public IEventListener {
public:
    bool HandleEvent(const IEvent& event) override {
        if (auto allocateEvent = dynamic_cast<const AllocateEvent*>(&event)) {
            std::cout << "AllocateEvent detected with size: " << allocateEvent->size << std::endl;
            return true;  // Event handled successfully
        }
        if (auto allocateEvent = dynamic_cast<const DeallocateEvent*>(&event)) {
            std::cout << "DeallocateEvent detected with size: " << allocateEvent->size << std::endl;
            return true;  // Event handled successfully
        }

        return false;  // Event not handled
    }
};


class Allocator {
public:
    void Allocate(size_t size) { 
        EventDispatcher::GetInstance().DispatchEvent(AllocateEvent(size));
        OnAllocate(size);
    }
    void Deallocate(size_t size) { 
        EventDispatcher::GetInstance().DispatchEvent(AllocateEvent(size));
        OnDeallocate(size);
    }

    using Event = BaseEvent<size_t>;
    Event OnAllocate;
    Event OnDeallocate;
};

int main() 
{
    auto allocateListener = std::make_shared<AllocateListener>();
    EventDispatcher::GetInstance().AddEventListener<AllocateEvent>(allocateListener);
    EventDispatcher::GetInstance().AddEventListener<DeallocateEvent>(allocateListener);
    
    // Trigger events   
    Allocator allocator;
    allocator.OnAllocate += [&](size_t size) {
        std::cout << "Allocator allocated size: " << size << std::endl;
    };
    allocator.OnDeallocate += [&](size_t size) {
        std::cout << "Allocator deallocated size: " << size << std::endl;
    };

    size_t size = 1337;
    allocator.Allocate(size);
    allocator.Deallocate(size);

    return 0;
}
