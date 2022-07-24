#pragma once

#include "Window.h"
#include "Events.h"
#include "Rendering/Renderer.h"

namespace SE
{
    class Application
    {
    public:
        inline Application(const char* title = "Application", const unsigned int width = 800, const unsigned int height = 600)
            : window(title, width, height), events(*this) {}
        inline void update()
        {
            while (!window.shouldClose())
            {
                if (events.isKey(SE::Key::ONE, SE::Action::PRESSED)) renderer.setPolygonMode(SE::PolygonMode::STANDARD);
                if (events.isKey(SE::Key::TWO, SE::Action::PRESSED)) renderer.setPolygonMode(SE::PolygonMode::WIREFRAME);

                onUpdate();

                window.swapBuffers();
                events.poll();
            }
        }

        virtual void processKeyboard() = 0;
        virtual void processMouseMovement(float xoffset, float yoffset) = 0;
        virtual void processScroll(float offset) = 0;

        Window window;
        Events events;
        Renderer renderer;

    protected:
        virtual void onUpdate() = 0;
    };
}

