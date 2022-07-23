#include "Rendering/Texture.h"

#define STB_IMAGE_IMPLEMENTATION // When we set it preprocessor modifies the header file such that it only contains the relevant definition source code, effectively turning the header file into a .cpp file
#include "stb/stb_image.h"

#include <glad/glad.h>

#include <string>
#include <mutex>

unsigned int SE::Texture::slotCount{ 0 };

SE::Texture::Texture(const char* imagePath, bool flipVertically)
{
    // Setting flipping:
    stbi_set_flip_vertically_on_load(flipVertically);

    // Loading image:
    int width, height;
    int nrChannels;// Number of color chanels.
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (!data) SE::Log::error({ "Failed to load image: ", imagePath });

    // Format-specific adjustments:
    std::string path = imagePath;
    int format;
    if (path.find(".jpg") != std::string::npos)         format = GL_RGB;
    else if (path.find(".png") != std::string::npos)    format = GL_RGBA;
    else
    {
        SE::Log::warning({ "Unexpected image format" });
        format = GL_RGB;
    }

    // Generating texture:
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Adjusting texture preferences:
    // * Texture wrapping:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // * Texture filtering:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);// NOTE: Mipmaps can only be applied when downscaling.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Attaching texture image to currently boud texture object:
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    // 2nd arg specifies the mipmap level we want to create texture for.
    // 3rd arg is in what kind of format we want to store our texture.
    // 6th arg is some legacy stuff. Sould always be 0.
    // 7th & 8th args specify the format and datatype of the source image file. // Looks like unigned byte = unsigned char.

    // NOTE: We can specify image for each mipmap level manually using the command above.
    // Or let OpenGL generate them automatically:
    glGenerateMipmap(GL_TEXTURE_2D);

    // Freeing image memory:
    stbi_image_free(data);

    // Binding texture to texture unit:
    // NOTE: Texture units are the slots, we bind texture to, to have multiple textures bound simultaneously.
    // NOTE: We can generate as many textures as OpenGL will allow us, but simultaneously bound can be only thoose, that are bound to texture unit.
    std::mutex mutex;
    mutex.lock();
    
    slot = slotCount++;
    textureUnit = GL_TEXTURE0 + slot;
    glActiveTexture(textureUnit); // Activating next free texture unit.

    mutex.unlock();
}

SE::Texture::~Texture()
{
    slot = 0;
    textureUnit = 0;
    glActiveTexture(0);
    glDeleteTextures(1, &id);
}

void SE::Texture::bind()
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);// Calling bind to currently active texture unit.
}
