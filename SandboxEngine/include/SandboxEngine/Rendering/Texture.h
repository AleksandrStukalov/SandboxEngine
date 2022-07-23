#pragma once

namespace SE
{
    class Texture
    {
    public:
        Texture(const char* imagePath, bool flipVertically = false);
        ~Texture();

        void bind();

        int slot;// NOTE: Necessarly int! NOT unsigned int!
    private:
        int textureUnit;
        unsigned int id;
        static unsigned int slotCount;
    };
}