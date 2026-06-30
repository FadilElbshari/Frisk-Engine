#include "OpenGL/OpenGLbuffer.h"
#include "Window/Buffer.h"
#include "glad/glad.h"


namespace Frisk {

    OpenGLvertexBuffer::OpenGLvertexBuffer(const void* a_Verts, U32 a_Size) {
        glGenBuffers(1, &m_VertexBufferID);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, a_Size, a_Verts, GL_STATIC_DRAW);
    }

    OpenGLvertexBuffer::OpenGLvertexBuffer(U32 a_Size) {
        glGenBuffers(1, &m_VertexBufferID);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, a_Size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLvertexBuffer::~OpenGLvertexBuffer() {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGLvertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }
    void OpenGLvertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLvertexBuffer::SetData(const void* a_Data, U32 a_Size) {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, a_Size, a_Data);
    }



    const VertexBufferLayout& OpenGLvertexBuffer::GetLayout() const {
        return m_Layout;
    }

    void OpenGLvertexBuffer::SetLayout(const VertexBufferLayout& a_Layout)  {
        m_Layout = a_Layout;
    }


    OpenGLindexBuffer::OpenGLindexBuffer(const U32* a_Indcs, U32 a_Size) : m_IndexCount(a_Size) {
        glGenBuffers(1, &m_IndexBufferID);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, a_Size, a_Indcs, GL_STATIC_DRAW);
    }

    OpenGLindexBuffer::OpenGLindexBuffer(U32 a_Size) : m_IndexCount(a_Size) {
        glGenBuffers(1, &m_IndexBufferID);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, a_Size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLindexBuffer::~OpenGLindexBuffer() {
        glDeleteBuffers(1, &m_IndexBufferID);
    }

    void OpenGLindexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    }
    void OpenGLindexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLindexBuffer::SetData(const U32* a_Data, U32 a_Size) {
        m_IndexCount = a_Size;
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, a_Size, a_Data);
    }

    U32 OpenGLindexBuffer::GetIndexCount() const {
        return m_IndexCount;
    }

}
