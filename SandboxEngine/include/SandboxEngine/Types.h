#pragma once

#include "Log.h"

namespace SE
{
    enum Type
    {
        FLOAT,
        DOUBLE,
        INT,
        UNSIGNED_INT,
    };

    unsigned int getPlatformType(SE::Type type);
    SE::Type getSEType(unsigned int type);
    inline unsigned int getSizeOfType(SE::Type type)
    {
        switch (type)
        {
        case SE::FLOAT:				return sizeof(float);
        case SE::DOUBLE:			return sizeof(double);
        case SE::INT:				return sizeof(int);
        case SE::UNSIGNED_INT:		return sizeof(unsigned int);
        default: SE::Log::error({ "Unsupported type" }); return -1;
        }
    }

}