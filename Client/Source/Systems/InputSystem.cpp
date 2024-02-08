#include "InputSystem.h"

InputSystem::InputSystem(entt::registry& registry)
    : ISystem(registry)
{

}

void InputSystem::Update(float deltaTime)
{
    GetRegistry().view<InputComponent>().each(
        [&](auto entity, InputComponent& input)
        {
            for (auto& [action, bindings] : input.actionBindings)
            {
                bool activeLastFrame = input.actionValues[action];
                input.actionValues[action] = false;
                for (auto& func : bindings)
                {
                    input.actionValues[action] = input.actionValues[action] || func();
                }
                if(input.actionValues[action] && !activeLastFrame)
                {
                    input.actionSignals[action].publish(entity);
                }
            }

            for (auto [axis, bindings] : input.axisBindings)
            {
                input.axisValues[axis] = 0.0f;
                for (auto& func : bindings)
                {
                    float axisValue = func();
                    input.axisValues[axis] += axisValue;
                }

                input.axisValues[axis] = std::clamp(input.axisValues[axis], -1.0f, 1.0f);
            }           
        });
}