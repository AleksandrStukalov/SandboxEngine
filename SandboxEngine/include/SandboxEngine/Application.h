#pragma once

#include "Window.h"
#include "Graphics/Renderer.h"

namespace SE
{
    float getTime();
    class Application
    {
    public:
        inline Application(const char* title = "Application", const unsigned int width = 800, const unsigned int height = 600)
            : window(title, width, height), events(*this) {}
        inline void update()
        {
            while (!window.shouldClose())
            {
                // Processing input:
                if (events.isKey(SE::Key::ESCAPE, SE::Action::PRESSED)) window.setShouldClose();
                if (events.isKey(SE::Key::ONE, SE::Action::PRESSED))    renderer.setPolygonMode(SE::PolygonMode::STANDARD);
                if (events.isKey(SE::Key::TWO, SE::Action::PRESSED))    renderer.setPolygonMode(SE::PolygonMode::WIREFRAME);
                processKeyboard();

                // Calculating delta time:
                float currentFrameTime = getTime();
                deltaTime = currentFrameTime - lastFrameTime;
                lastFrameTime = currentFrameTime;

                onUpdate();

                window.swapBuffers();
                events.poll();
            }
        }

        virtual void processKeyboard(){};
        virtual void processMouseMovement(float xoffset, float yoffset){};
        virtual void processScroll(float offset){};

        Window window;
        Events events;
        Renderer renderer;
        float deltaTime{0.0f};

    protected:
        virtual void onUpdate() = 0;

    private:
        float lastFrameTime{0.0f};
    };
}

