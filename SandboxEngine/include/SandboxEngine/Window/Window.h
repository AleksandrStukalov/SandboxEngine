#pragma once

namespace SE
{
    enum class CursorMode
    {
        STANDARD,
        CAPTURE,
        HIDDEN
    };

    class Window
    {
    public:
        Window(const char* title, const unsigned int width, const unsigned int height);
        ~Window();

        bool shouldClose();
        void setShouldClose();
        void swapBuffers();
        void setCursorMode(CursorMode mode);

        void* handle;
        unsigned int width, height;
    };
}