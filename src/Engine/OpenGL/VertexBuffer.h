#ifndef BLOCKBUILDINGGAME_VERTEXBUFFER_H
#define BLOCKBUILDINGGAME_VERTEXBUFFER_H

namespace engine {

#include "glad/glad.h"

    class VertexBuffer
    {
    private:
        unsigned int m_bufferID;
    public:
        VertexBuffer(const void* dataArray, unsigned int size, GLenum usage);
        ~VertexBuffer();

        void Bind() const;
        /*
         * not static for more consistent style.
         * vb.Bind() and vb.Unbind() instead of VertexBuffer::Unbind()
         */
        inline void Unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };

}

#endif //BLOCKBUILDINGGAME_VERTEXBUFFER_H
