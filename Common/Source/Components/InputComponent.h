#pragma once

//////////////////////////////////////////////////////////
// Standard Library Headers
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Project Headers
//////////////////////////////////////////////////////////

#include "IComponent.h"

//////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Class Declaration
//////////////////////////////////////////////////////////

enum class ControllerButtons {
    A,
    B,
    X,
    Y,
    LB,
    RB,
    Back,
    Start,
    L,
    R,
};

enum class ControllerAxis {
    LStickH = sf::Joystick::Axis::X,
    LStickV = sf::Joystick::Axis::Y,
    LRTrigger = sf::Joystick::Axis::Z,
    RStickH = sf::Joystick::Axis::U,
    RStickV = sf::Joystick::Axis::R,
    DPadH = sf::Joystick::Axis::PovX,
    DPadV = sf::Joystick::Axis::PovY,
};

enum class InputAxis {
    Vertical,
    Horizontal,
};

enum class InputAction {
    ZoomIn,
    ZoomOut,
    PanLeft,
    PanRight,
    PanUp,
    PanDown,
    MouseMiddle,
    ConstructBuilding,
    Cancel
};

class InputComponent : public IComponent {
public:
    typedef std::function<float()> AxisBindingFunc;
    typedef std::function<bool()> ActionBindingFunc;
    
    std::unordered_map<InputAxis, std::vector<AxisBindingFunc>> axisBindings;
    std::unordered_map<InputAction, std::vector<ActionBindingFunc>> actionBindings;
    
    std::unordered_map<InputAxis, float> axisValues;
    std::unordered_map<InputAction, bool> actionValues;

    std::unordered_map<InputAction, entt::sigh<void(entt::entity)>> actionSignals;

    void AddAxisBinding(InputAxis axis, sf::Keyboard::Key positive, sf::Keyboard::Key negative);
    void AddAxisBinding(InputAxis axis, unsigned int joystickId, sf::Joystick::Axis joystickAxis);

    entt::sink<entt::sigh<void(entt::entity)>> GetActionSignal(InputAction action);

    void AddActionBinding(InputAction action, sf::Keyboard::Key key);
    void AddActionBinding(InputAction action, unsigned int joystickId, int joystickButton);
    void AddActionBinding(InputAction action, unsigned int joystickId, sf::Joystick::Axis joystickAxis, float triggerValue);
    void AddActionBinding(InputAction action, sf::Mouse::Button mouseButton);
};

