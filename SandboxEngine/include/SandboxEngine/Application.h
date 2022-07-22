#pragma once

#include "Window.h"

namespace SE
{
    class Application
    {
    public:
        inline Application(const char* title = "Application", const unsigned int width = 800, const unsigned int height = 600)
            : window(title, width, height) {}
        inline void update()
        {
            while (!window.shouldClose())
            {
                onUpdate();

                window.swapBuffers();
            }
        }

        Window window;

    protected:
        virtual void onUpdate() = 0;
    };
}

