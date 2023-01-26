#include "IndexBuffer.h"

namespace engine
{
    IndexBuffer::IndexBuffer(const void* dataArray, unsigned int size, GLenum usage)
    {
        glGenBuffers(1, &m_bufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, dataArray, usage);
        Unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        Unbind();
        glDeleteBuffers(1, &m_bufferID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    }

}