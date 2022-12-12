#ifndef BLOCKBUILDINGGAME_INDEXBUFFER_H
#define BLOCKBUILDINGGAME_INDEXBUFFER_H

#include "glad/glad.h"

namespace engine
{
    class IndexBuffer
    {
    private:
        unsigned int m_bufferID;
    public:

        IndexBuffer(const void* dataArray, unsigned int size, GLenum usage);
        ~IndexBuffer();

        void Bind() const;

        /*
         * not static for more consistent style.
         * vb.Bind() and vb.Unbind() instead of VertexBuffer::Unbind()
         */
        inline void Unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    };
}

#endif //BLOCKBUILDINGGAME_INDEXBUFFER_H
