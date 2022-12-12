#include "VertexBuffer.h"

namespace engine {

    VertexBuffer::VertexBuffer(const void* dataArray, unsigned int size, GLenum usage)
    {
        glGenBuffers(1, &m_bufferID);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, dataArray, usage);
        Unbind();
    }

    VertexBuffer::~VertexBuffer()
    {
        Unbind();
        glDeleteBuffers(1, &m_bufferID);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    }
}
