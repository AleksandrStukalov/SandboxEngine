#pragma once

#include <string>

namespace SE
{
    class Shader
    {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
        void bind() const;

        void setUniform(SE::Type type, const std::string name, const void* data);

        unsigned int program;
    private:
        std::string getSource(const char* shaderPath);
        void compile(unsigned int shaderType, unsigned int shader);
        unsigned int create(unsigned int shaderType, const char* source);
        void link(unsigned int shader);
    };
    
}