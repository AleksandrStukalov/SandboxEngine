#pragma once

#include "Input.h"

namespace SE
{
    class Application;
    class Events
    {
    public:
        Events(SE::Application& application);

        void poll() const;

        bool isKey(SE::Key, SE::Action action);
        bool isMouseButton(SE::MouseButton mouseButton, SE::Action action);


        bool toggleKeys[120];
        bool toggleMouseButtons[7];
    private:
        SE::Application& application;
    };
}