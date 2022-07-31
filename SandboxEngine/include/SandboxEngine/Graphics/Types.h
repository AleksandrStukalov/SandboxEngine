#pragma once

#include "SandboxEngine/Log.h"

namespace SE
{
    enum Type
    {
        FLOAT,
        DOUBLE,
        INT,
        UNSIGNED_INT,
        FLOAT_VEC2,
        FLOAT_VEC3,
        MAT4F,
    };

    unsigned int getPlatformType(SE::Type type);
    SE::Type getSEType(unsigned int type);
    inline unsigned int getSizeOfType(SE::Type type)
    {
        switch (type)
        {
        case SE::FLOAT:             return sizeof(float);
        case SE::DOUBLE:            return sizeof(double);
        case SE::INT:               return sizeof(int);
        case SE::UNSIGNED_INT:      return sizeof(unsigned int);
        case SE::FLOAT_VEC2:        return sizeof(float) * 2;
        case SE::FLOAT_VEC3:        return sizeof(float) * 3;
        case SE::MAT4F:              return sizeof(float) * 4;

        default: SE::Log::error({ "No size definition for type: ", (const char*)type }); return -1;
        }
    }

}