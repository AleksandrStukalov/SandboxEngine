#include "GLFWContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <thread>
#include <mutex>

// NOTE: GLFW context is single for each window, and therefore we need to get sure, it was initialized only one time.

static std::mutex mutex;

static bool glfwInitialized{ false };

SE::GLFWContext::~GLFWContext()
{
    mutex.lock();

    if (glfwInitialized)
    {
        glfwInitialized = false;
        glfwTerminate();
    }

    mutex.unlock();
}

void SE::GLFWContext::init()
{
    mutex.lock();

    if (!glfwInitialized)
    {
        glfwInitialized = true;
        if (!glfwInit())
        {
            SE::Log::error({ "Failed to initialize glfw" });
        }
    }

    mutex.unlock();
}