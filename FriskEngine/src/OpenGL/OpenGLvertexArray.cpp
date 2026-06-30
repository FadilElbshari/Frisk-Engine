#include "OpenGL/OpenGLvertexArray.h"

#include "OpenGL/OpenGLbuffer.h"
#include "Window/Buffer.h"
#include "glad/glad.h"
#include "Engine/Core/Log.h"

namespace Frisk {
    OpenGLvertexArray::OpenGLvertexArray() : m_VertexAttribCounter(0) {
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

    void OpenGLvertexArray::AssignVertexBuffer(std::unique_ptr<VertexBuffer>& a_VBO) {
        Bind();
        a_VBO->Bind();

        auto& layout = a_VBO->GetLayout();
        auto& comp_list = layout.GetComponentList();

        for (const auto& comp : comp_list) {
            // float check
            if (comp.type >= VertexDataType::Float && comp.type <= VertexDataType::Float4) {
                glVertexAttribPointer(m_VertexAttribCounter, comp.GetInternalComponentCount(), GL_FLOAT, comp.normalised ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<void*>(comp.offset));
                Log::Info(comp.type == VertexDataType::Float3, " ", comp.GetInternalComponentCount(), " ", comp.offset, " ", m_VertexAttribCounter, comp.normalised ? GL_TRUE : GL_FALSE, "\n");
                glEnableVertexAttribArray(m_VertexAttribCounter);
                m_VertexAttribCounter++;
            }
            // matrices
            else if (comp.type >= VertexDataType::Mat3 && comp.type <= VertexDataType::Mat4) {
                for (U32 i{}; i < comp.GetInternalComponentCount(); i++) {
                    glVertexAttribPointer(m_VertexAttribCounter, comp.GetInternalComponentCount(), GL_FLOAT, comp.normalised ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<void*>(comp.offset));
                    glEnableVertexAttribArray(m_VertexAttribCounter++);
                }
            }
            // ints and bool
            else if (comp.type >= VertexDataType::Int && comp.type <= VertexDataType::Bool) {
                glVertexAttribIPointer(m_VertexAttribCounter, comp.GetInternalComponentCount(), GL_INT, layout.GetStride(), reinterpret_cast<void*>(comp.offset));
                glEnableVertexAttribArray(m_VertexAttribCounter++);
            }
        }

    }
}
