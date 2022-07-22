#include "SandboxEngine.h"
#include "SandboxEngine/Window.h"

#include <iostream>
#include <sstream>

class App : public SE::Application
{
    void onUpdate() override
    {
        if (events.isKey(SE::Key::A, SE::KeyAction::PRESSED))
        {
            SE::Log::info({ "A pressed" });
        }
        if (events.isMouseButton(SE::MouseButton::LEFT, SE::KeyAction::PRESSED))
        {
            SE::Log::info({ "LMB" });
        }
    }

    void processMouseMovement(float xoffset, float yoffset) override
    {
        std::stringstream message; 
        message << "xoffset: "; 
        message << xoffset;
        message << "\t yoffset: ";
        message << yoffset;
        SE::Log::info({ message.str() });
    }
};

int main()
{
    App app;
    app.update();
}