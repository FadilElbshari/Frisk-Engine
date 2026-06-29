#include "OpenGL/OpenGLvertexArray.h"

#include "OpenGL/OpenGLbuffer.h"
#include "Window/Buffer.h"
#include "glad/glad.h"

namespace Frisk {
    OpenGLvertexArray::OpenGLvertexArray() {
        glGenVertexArrays(1, &m_VertexArrayID);
    }

    OpenGLvertexArray::~OpenGLvertexArray() {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }


    void OpenGLvertexArray::Bind() const {
        glBindVertexArray(m_VertexArrayID);
    }

    void OpenGLvertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLvertexArray::AssignVertexBuffer(VertexBuffer& a_VBO) {

    }
}
