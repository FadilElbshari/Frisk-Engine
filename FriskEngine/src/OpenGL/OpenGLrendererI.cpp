#include "OpenGL/OpenGLrendererI.h"

namespace Frisk
{

    OpenGLrendererI::~OpenGLrendererI() {}

    void OpenGLrendererI::Init()
    {
        float verts[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

        U32 indcs[] = {0, 1, 2, 2, 3, 0};

        m_Data.StartOfData = new InstancedData[MAX_QUADS_INSTANCED];
        m_Data.Data = m_Data.StartOfData;

        m_Data.VAO = VertexArray::Create();
        m_Data.VBObase = VertexBuffer::Create(verts, sizeof(verts));
        m_Data.VBObase->SetLayout(VertexBufferLayout({VertexBufferComponent("Position", VertexDataType::Float3)}));

        m_Data.VBOinstanced = VertexBuffer::Create(MAX_QUADS_INSTANCED * sizeof(InstancedData));
        m_Data.VBOinstanced->SetLayout(
            VertexBufferLayout({VertexBufferComponent("translation", VertexDataType::Float3, true),
                                VertexBufferComponent("size", VertexDataType::Float3, true),
                                VertexBufferComponent("color", VertexDataType::Float3, true)}));

        m_Data.IBO = IndexBuffer::Create(indcs, sizeof(indcs));

        m_Data.VAO->AssignVertexBuffer(m_Data.VBObase);
        m_Data.VAO->AssignVertexBuffer(m_Data.VBOinstanced);
        m_Data.VAO->AssignIndexBuffer(m_Data.IBO);
    }

    void OpenGLrendererI::Beginframe()
    {
        m_Data.Data = m_Data.StartOfData;
        m_Data.InstanceCount = 0;
    }

    void OpenGLrendererI::Submitquad(const VEC3 &a_Position, const VEC3 &a_Size, const VEC3 &a_Color)
    {
        *(m_Data.Data++) = {a_Position, a_Size, a_Color / 255.0f};
        m_Data.InstanceCount++;
    }

    void OpenGLrendererI::Assembleframe()
    {
        m_Data.VBOinstanced->SetData(m_Data.StartOfData, m_Data.InstanceCount * sizeof(InstancedData));
    }

    void OpenGLrendererI::Endframe()
    {
        Assembleframe();
        m_Data.VAO->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, m_Data.IBO->GetIndexCount(), GL_UNSIGNED_INT, nullptr,
                                m_Data.InstanceCount);
    }

    void OpenGLrendererI::Shutdown()
    {
        if (m_Data.StartOfData != nullptr)
            delete[] m_Data.StartOfData;
    }
} // namespace Frisk
