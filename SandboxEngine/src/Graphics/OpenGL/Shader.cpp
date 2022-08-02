#include "Graphics/Shader.h"

#include <glad/glad.h>

#include <fstream>

void SE::Shader::setUniform(SE::Type type, const std::string name,  const void* data)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    if (location == -1) SE::Log::warning({ "Uniform", name, " doesn't exist" });
    bind();
    switch (type)
    {
    case SE::FLOAT:         glUniform1f(location,  *(float*)data);                      break;
    case SE::DOUBLE:        glUniform1d(location,  *(double*)data);                     break;
    case SE::INT:           glUniform1i(location,  *(int*)(data));                      break;
    case SE::UNSIGNED_INT:  glUniform1ui(location, *(unsigned int*)data);               break;
    case SE::FLOAT_VEC2:    glUniform2fv(location, 1, (float*)data);                    break;
    case SE::FLOAT_VEC3:    glUniform3fv(location, 1, (float*)data);                    break;
    case SE::MAT4F:         glUniformMatrix4fv(location, 1, GL_FALSE, (float*)data);    break;
    default: SE::Log::error({ "Unsupported uniform type" });
    }
    // NOTE: for glUniform{...}f count parameter is how many instances of vector, matrices or whatever we want to send, 
    // and in this case last parameter sould be an array of this instances.
    // This feature allows us to save some API calls by loading all the instances in one call.
}

void SE::Shader::bind() const { glUseProgram(program); }

SE::Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexShaderSource = getSource(vertexShaderPath);
    std::string fragmentShaderSource = getSource(fragmentShaderPath);

    unsigned int vertexShader = create(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    unsigned int fragmentShader = create(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    link(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

SE::Shader::~Shader() { glDeleteProgram(program); }

std::string SE::Shader::getSource(const char* shaderPath)
{
    std::fstream shaderFile(shaderPath);

    if (!shaderFile) SE::Log::error({ "Invalid shader file path: ", shaderPath });

    std::string shaderSource;
    std::string line;
    while (std::getline(shaderFile, line))
    {
        shaderSource += line + "\n";
    }
    shaderSource += '\0';
    shaderFile.close();

    return shaderSource;
}

void SE::Shader::compile(unsigned int shaderType, unsigned int shader)
{
    glCompileShader(shader);

    int result;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == false)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        SE::Log::error({ "Failed to compile ", shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", " shader\n", (std::string)infoLog + '\n' });
    }
}

unsigned int SE::Shader::create(unsigned int shaderType, const char* source)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    // NOTE: If length parameter is NULL, then every line is assumed to be null-terminated.
    compile(shaderType, shader);
    return shader;
}

void SE::Shader::link(unsigned int shader)
{
    glLinkProgram(program);
    int result;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == false)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        SE::Log::error({ "Failed to link shader program: ",  infoLog + '\n' });
    }
}