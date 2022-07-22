#pragma once

#include <iostream>
#include <vector>
#include <string>

// Example usecase: SE::Log::info({ "Hello", "World" });
namespace SE
{
    class Log
    {
    public:
        inline static void info(std::vector<std::string> message)
        {
            message.insert(message.begin(), "Info: ");
            print(message);
        }
        inline static void warning(std::vector<std::string> message)
        {
            message.insert(message.begin(), "Warning: ");
            print(message);
        }
        inline static void error(std::vector<std::string> message)
        {
            message.insert(message.begin(), "Error: ");
            print(message);
            __debugbreak();
        }

    private:
        inline static void print(const std::vector<std::string> message)
        {

        #ifndef NDEBUG
            for (auto element : message)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        #endif

        }
    };
}