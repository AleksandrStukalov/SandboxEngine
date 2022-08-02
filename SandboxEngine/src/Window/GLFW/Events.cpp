#include "Window/Events.h"
#include "Application.h"

#include <GLFW/glfw3.h>

float SE::getTime() { return (float)glfwGetTime(); }

void SE::Events::poll() const { glfwPollEvents(); }

// Callbacks:
void errorCallback(int error_code, const char* description)
{
    SE::Log::error({ "GLFW: ", description });
}
void framebufferSizeCallback(GLFWwindow* handle, int width, int height)
{
    SE::Application& application = *static_cast<SE::Application*>(glfwGetWindowUserPointer(handle));
    application.window.width = width;
    application.window.height = height;
    application.renderer.viewport(0, 0, width, height);
}
void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    SE::Application& application = *(SE::Application*)(glfwGetWindowUserPointer(handle));
    SE::Events& events = application.events;

    if (action == GLFW_PRESS)
    {
        // Toggling keys:
        bool& state = events.toggleKeys[(int)SE::getSEKey(key)];
        state = !state;
    }

   // application.processKeyboard(); // NEVER!!!
}
bool SE::Events::isKey(SE::Key key, SE::Action action)
{
    GLFWwindow* window = (GLFWwindow*)application.window.handle;
    switch (action)
    {
    case SE::Action::PRESSED:
        return glfwGetKey(window, SE::getPlatformKey(key)) == GLFW_PRESS;
    case SE::Action::RELEASED:
        return glfwGetKey(window, SE::getPlatformKey(key)) == GLFW_RELEASE;
    case SE::Action::TOGGLE:
        return toggleKeys[(int)key];
    default:
        SE::Log::error({ "Unsupported key action" });
    }
}
void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    SE::Application& application = *(SE::Application*)(glfwGetWindowUserPointer(handle));
    SE::Events& events = application.events;

    if (action == GLFW_PRESS)
    {
        // Toggling mouse buttons:
        bool& state = events.toggleMouseButtons[(int)SE::getSEMouseButton(button)];
        state = !state;
    }
}
bool SE::Events::isMouseButton(SE::MouseButton mouseButton, SE::Action action)
{
    GLFWwindow* window = (GLFWwindow*)application.window.handle;
    switch (action)
    {
    case SE::Action::PRESSED:
        return glfwGetMouseButton(window, SE::getPlatformMouseButton(mouseButton)) == GLFW_PRESS;
    case SE::Action::RELEASED:
        return glfwGetMouseButton(window, SE::getPlatformMouseButton(mouseButton)) == GLFW_RELEASE;
    case SE::Action::TOGGLE:
        return toggleMouseButtons[(int)mouseButton];
    default:
        SE::Log::error({ "Unsupported mouse button action" });
    }
}
bool firstCursorPos(true);// For checking whether or not cursor just entered window borders
float lastX(0.0f), lastY(0.0f);
void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
{
    SE::Application& application = *(SE::Application*)glfwGetWindowUserPointer(handle);

    if (firstCursorPos)
    {
        lastX = xpos;
        lastY = ypos;
        firstCursorPos = false;
    }
    // NOTE: It's needed to circumvent sudden jump of the offset, when cursor enters window borders.

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    application.processMouseMovement(xoffset, yoffset);
}
void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset)
{
    SE::Application& application = *(SE::Application*)glfwGetWindowUserPointer(handle);
    application.processScroll(yoffset);
}

SE::Events::Events(SE::Application& application)
    : application(application)
{
    // Clearing toggle keys:
    for (bool& key : toggleKeys) { key = false; }

    GLFWwindow* window = (GLFWwindow*)application.window.handle;
    glfwSetWindowUserPointer(window, &application);

    // Setting callbacks:
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
}