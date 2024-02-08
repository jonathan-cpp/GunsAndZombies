#include "Components.h"

float GetAxisValue(sf::Keyboard::Key positive, sf::Keyboard::Key negative)
{
    return static_cast<float>(static_cast<int>(sf::Keyboard::isKeyPressed(positive)) - static_cast<int>(sf::Keyboard::isKeyPressed(negative)));
}

void InputComponent::AddAxisBinding(InputAxis axis, sf::Keyboard::Key positive, sf::Keyboard::Key negative) 
{
    axisBindings[axis].push_back([=](){ return GetAxisValue(positive, negative); });
}

void InputComponent::AddAxisBinding(InputAxis axis, unsigned int joystickId, sf::Joystick::Axis joystickAxis) 
{
    axisBindings[axis].push_back([=](){ return sf::Joystick::getAxisPosition(joystickId, joystickAxis) / 100.0f; });
}

entt::sink<entt::sigh<void(entt::entity)>> InputComponent::GetActionSignal(InputAction action)
{
    return entt::sink(actionSignals[action]);
}

void InputComponent::AddActionBinding(InputAction action, sf::Keyboard::Key key)
{
    actionBindings[action].push_back([=](){ return sf::Keyboard::isKeyPressed(key); });
}

void InputComponent::AddActionBinding(InputAction action, unsigned int joystickId, int joystickButton)
{
    actionBindings[action].push_back([=](){ return sf::Joystick::isButtonPressed(joystickId, joystickButton); });
}

void InputComponent::AddActionBinding(InputAction action, unsigned int joystickId, sf::Joystick::Axis joystickAxis, float triggerValue) 
{
    actionBindings[action].push_back([=](){ 
        float value = sf::Joystick::getAxisPosition(joystickId, joystickAxis) / 100.f;
        if(std::signbit(triggerValue)) {
            return value - triggerValue <= 0.0f;
        } 
        else {
            return value - triggerValue >= 0.0f;
        }
    });
}

void InputComponent::AddActionBinding(InputAction action, sf::Mouse::Button mouseButton)
{
    actionBindings[action].push_back([=](){ return sf::Mouse::isButtonPressed(mouseButton); });
}