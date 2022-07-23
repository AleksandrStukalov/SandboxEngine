#include "Rendering/Shader.h"

#include <glad/glad.h>

#include <fstream>

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

void SE::Shader::bind() { glUseProgram(program); }

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

void SE::Shader::setUniform(SE::Type type, std::string name, void* data)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    if (location == -1) SE::Log::warning({ "Uniform", name, " doesn't exist" });
    bind();
    switch (type)
    {
    case SE::FLOAT:         glUniform1f(location,  *(float*)data);          break;
    case SE::DOUBLE:        glUniform1d(location,  *(double*)data);         break;
    case SE::INT:           glUniform1i(location,  *(int*)(data));          break;
    case SE::UNSIGNED_INT:  glUniform1ui(location, *(unsigned int*)data);   break;
    default: SE::Log::error({ "Unsupported uniform type" });
    }
}