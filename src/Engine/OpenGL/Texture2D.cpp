#include "Texture2D.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace engine
{
    Texture2D::Texture2D(const char *texturePath, GLenum inputFormat, int internalFormat,
                         int sAxisWarpMode, int tAxisWarpMode, int downscalingFilter, int upscalingFilter, bool mipmap)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sAxisWarpMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tAxisWarpMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, downscalingFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, upscalingFilter);

        stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, inputFormat, GL_UNSIGNED_BYTE, data);
            if(mipmap)
            {
                GenerateMipmaps();
            }
        }
        else
        {
            std::cout << "Error reading Texture Image (" << texturePath << ")"  << std::endl;
        }

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_textureID);
    }

    void Texture2D::GenerateMipmaps() const
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    unsigned int Texture2D::GetTextureID() const
    {
        return m_textureID;
    }

    void Texture2D::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::SetTextureSlot(int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }
}