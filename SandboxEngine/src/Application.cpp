#include "Application.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

GLFWwindow* window;

SE::Application::Application()
{
    /* Initialize the library */
    if (!glfwInit())
        SE::Log::error({"GLFW initialization failed"});

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        SE::Log::error({"Failed to create window"});
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}

SE::Application::~Application()
{
    
}

void SE::Application::update()
{
    while (!glfwWindowShouldClose(window))
    {

        onUpdate();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void SE::Application::onUpdate()
{
    
}
