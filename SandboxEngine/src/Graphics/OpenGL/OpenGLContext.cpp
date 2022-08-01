#include "D:/Development/SandboxEngine/SandboxEngine/CMakeFiles/SandboxEngine.dir/Debug/cmake_pch.hxx"
#include "OpenGLContext.h"

#include <glad/glad.h>

#include <sstream>

// If debug mode enabled, it displays errors, thrown by OpenGL
void APIENTRY debugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* debugMessage, const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 1280) return;
    // 131185 - NVIDIA's drivers buffer successfully created message.
    // 1280 - GL_INVALID_ENUM error generated. <texture> exceeds the maximum supported number of combined texture image units. // Shows after closure for some reason.

    std::stringstream message;
    message << "OpenGL (id: " << id << ") " << debugMessage << '\n';

    message << "Source: ";
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:               message << "API";                                                               break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     message << "Window System";                                                     break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:   message << "Shader Compiler";                                                   break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:       message << "Third Party";                                                       break;
    case GL_DEBUG_SOURCE_APPLICATION:       message << "Application";                                                       break;
    case GL_DEBUG_SOURCE_OTHER:             message << "Other";                                                             break;
    default:                                message << "Unhandled source " << source;                                       break;
    }message << '\t';

    message << "Type: ";
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               message << "Error";                                                             break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: message << "Deprecated Behaviour";                                              break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  message << "Undefined Behaviour";                                               break;
    case GL_DEBUG_TYPE_PORTABILITY:         message << "Portability";                                                       break;
    case GL_DEBUG_TYPE_PERFORMANCE:         message << "Performance";                                                       break;
    case GL_DEBUG_TYPE_MARKER:              message << "Marker";                                                            break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          message << "Push Group";                                                        break;
    case GL_DEBUG_TYPE_POP_GROUP:           message << "Pop Group";                                                         break;
    case GL_DEBUG_TYPE_OTHER:               message << "Other";                                                             break;
    default:                                message << "Unhandled type " << type;                                           break;
    }message << '\t';


    void (*logFunc)(std::vector<std::string>);// Function pointer for containing SE::Log:: ...
    message << "Severity: ";
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:            message << "High";                              logFunc = SE::Log::error;       break;
    case GL_DEBUG_SEVERITY_MEDIUM:          message << "Medium";                            logFunc = SE::Log::error;       break;
    case GL_DEBUG_SEVERITY_LOW:             message << "Low";                               logFunc = SE::Log::warning;     break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:    message << "Notification";                      logFunc = SE::Log::info;        break;
    default:                                message << "Unhandled severity " << severity;   logFunc = SE::Log::warning;     break;
    }

    logFunc({ message.str(), "\n\n" });
}

void SE::OpenGLContext::init()
{
    // Initializing GLAD:
    if (!gladLoadGL()) SE::Log::error({ "Failed to initialize glad" });

    // Setting debug mode:
#ifndef NDEBUG
    // Taking all context flags:
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    // Checking if debug context is initialized successfully:
    if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) SE::Log::error({ "Failed to initialize OpenGL's debug context" });

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);// Tells OpenGL to call debug message function straight after an error occured.
    glDebugMessageCallback(debugMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);// Filters messages by their parameters.
    // NOTE: When GL_DONT_CARE is set, parameter does not participate in filtering, which means, that we will get all its types. In this case we do not filter messages at all, and are printing all of them.
    // NOTE: We can push our own messages to debug message callback, by using glDebugMessageInsert(...). Example usecase: (GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0, GL_DEBUG_SEVERITY_MEDIUM, -1, "error message here")
#endif //NDEBUG

    // Configurating state:
     glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);// Sets triangles, that get rendered in clockwise order, as front-fasing.
    //glCullFace(GL_BACK);// Sets back-facing triangles to be culled.

}
