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
        unsigned int vertexCount;
    public:
        VertexArrayObject();
        ~VertexArrayObject();

        void AddIndexBuffer(IndexBuffer &ib) const;
        void SetVertexAttribPointer(VertexBuffer &vb, unsigned int index, int size, GLenum type, bool normalized, int stride, const void* offset);

        void EnableVertexAttribPointer(unsigned int index) const;
        void DisableVertexAttribPointer() const;

        void Bind() const;
        /*
         * not static for more consistent style.
         * vao.Bind() and vao.Unbind() instead of VertexArrayObject::Unbind()
         */
        inline void Unbind() const
        {
            glBindVertexArray(0);
        }

        inline unsigned int GetVertexCount() {return vertexCount;}
        inline void SetVertexCount(unsigned count) {vertexCount = count;}
    };

}

#endif //BLOCKBUILDINGGAME_VERTEXARRAYOBJECT_H
