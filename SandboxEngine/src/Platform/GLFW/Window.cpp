#include "Window.h"
#include "Application.h"
#include "GLFWContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

SE::Window::Window(const char* title, const unsigned int width, const unsigned int height)
    : width(width), height(height)
{
    // Initializing GLFW:
    SE::GLFWContext::init();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // NOTE: We use OpenGL 4.3 minimal required version, because only 4.3 and above has debug output callback functionality.

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);// Enabling OpenGL's debug context, in which it sends error descriptions to our debug output callback.
#endif // NDEBUG

    // Creating window:
    handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!handle) SE::Log::error({ "Failed to initialize window" });

    glfwMakeContextCurrent((GLFWwindow*)handle);
    glfwSwapInterval(1);// VSync
}

SE::Window::~Window()
{
    glfwDestroyWindow((GLFWwindow*)handle);
}

bool SE::Window::shouldClose()
{
    return glfwWindowShouldClose((GLFWwindow*)handle);
}

void SE::Window::setShouldClose()
{
    glfwSetWindowShouldClose((GLFWwindow*)handle, true);
}

void SE::Window::swapBuffers()
{
    glfwSwapBuffers((GLFWwindow*)handle);
}

void SE::Window::setCursorMode(CursorMode mode)
{
    switch (mode)
    {
    case CursorMode::STANDARD:    glfwSetInputMode((GLFWwindow*)handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break;
    case CursorMode::CAPTURE:     glfwSetInputMode((GLFWwindow*)handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
    case CursorMode::HIDDEN:      glfwSetInputMode((GLFWwindow*)handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); break;
    default:                      SE::Log::error({ "Unsupported cursor mode" });
    }
}