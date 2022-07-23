#include "Types.h"

#include <GLAD/glad.h>


unsigned int SE::getPlatformType(SE::Type type)
{
    switch (type)
    {
    case SE::FLOAT:             return GL_FLOAT;
    case SE::DOUBLE:            return GL_DOUBLE;
    case SE::INT:               return GL_INT;
    case SE::UNSIGNED_INT:      return GL_UNSIGNED_INT;

    default: SE::Log::error({ "Unsupported type" }); return -1;
    }
}

SE::Type SE::getSEType(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT:              return SE::FLOAT;
    case GL_DOUBLE:             return SE::DOUBLE;
    case GL_INT:                return SE::INT;
    case GL_UNSIGNED_INT:       return SE::UNSIGNED_INT;
    default: SE::Log::error({ "Unsupported type" }); return SE::Type();
    }
}