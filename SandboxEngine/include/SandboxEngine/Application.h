#pragma once

#include "Window.h"
#include "Events.h"

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
                onUpdate();

                window.swapBuffers();
                events.poll();
            }
        }

        virtual void processMouseMovement(float xoffset, float yoffset) = 0;

        Window window;
        Events events;

    protected:
        virtual void onUpdate() = 0;
    };
}

