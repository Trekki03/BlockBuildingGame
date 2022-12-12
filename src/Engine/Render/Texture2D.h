#ifndef BLOCKBUILDINGGAME_TEXTURE2D_H
#define BLOCKBUILDINGGAME_TEXTURE2D_H

#include <glad/glad.h>

namespace engine
{

    class Texture2D
    {
    private:
        unsigned int m_textureID{};

    public:
        Texture2D(const char *texturePath, GLenum inputFormat, int internalFormat,
                  int sAxisWarpMode, int tAxisWarpMode, int downscalingFilter, int upscalingFilter, bool mipmap);
        ~Texture2D();

        /*
         * not static for more consistent style.
         */
        void GenerateMipmaps() const;
        [[nodiscard]] unsigned int GetTextureID() const;
        void Bind() const;
        /*
         * not static for more consistent style.
         */
        void Unbind() const;
        void SetTextureSlot(int slot) const;
    };

}

#endif //BLOCKBUILDINGGAME_TEXTURE2D_H
