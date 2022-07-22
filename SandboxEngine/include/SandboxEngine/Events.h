#pragma once

#include "Input.h"

namespace SE
{
    class Application;
    class Events
    {
    public:
        Events(SE::Application& application);

        void poll();

        bool isKey(SE::Key, SE::KeyAction action);
        bool isMouseButton(SE::MouseButton mouseButton, SE::KeyAction action);


        bool toggleKeys[120];
        bool toggleMouseButtons[7];
    private:
        SE::Application& application;
    };
}