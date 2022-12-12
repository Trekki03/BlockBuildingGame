#ifndef BLOCKBUILDINGGAME_VERTEXARRAYOBJECT_H
#define BLOCKBUILDINGGAME_VERTEXARRAYOBJECT_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace engine
{

    class VertexArrayObject
    {
    private:
        unsigned int m_ObjectID{};
    public:
        VertexArrayObject();
        ~VertexArrayObject();

        void AddIndexBuffer(IndexBuffer &ib) const;
        void SetVertexAttribPointer(VertexBuffer &vb, unsigned int index, int size, GLenum type, bool normalized, int stride, const void* offset) const;

        void EnableVertexAttribPointer(unsigned int index) const;
        void DisableVertexAttribPointer() const;

        void Bind() const;
        /*
         * not static for more consistent style.
         * vb.Bind() and vb.Unbind() instead of VertexBuffer::Unbind()
         */
        inline void Unbind() const
        {
            glBindVertexArray(0);
        }
    };

}

#endif //BLOCKBUILDINGGAME_VERTEXARRAYOBJECT_H
