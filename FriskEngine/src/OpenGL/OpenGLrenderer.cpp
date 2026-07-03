#include "OpenGL/OpenGLrenderer.h"
#include "pch.h"

namespace Frisk {

	OpenGLrenderer::~OpenGLrenderer() {

	}

	void OpenGLrenderer::Init() {
		m_Data.VAO = VertexArray::Create();
		m_Data.VBO = VertexBuffer::Create(sizeof(QuadData) * MAX_VERTS);
		m_Data.VBO->SetLayout(VertexBufferLayout({ VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3) }));

		m_Data.IBO = IndexBuffer::Create(sizeof(U32) * MAX_INDCS);

		m_Data.VAO->AssignVertexBuffer(m_Data.VBO);
		m_Data.VAO->AssignIndexBuffer(m_Data.IBO);

		m_Data.StartOfDataPointer = new QuadData[MAX_VERTS];
		m_Data.VertexDataBuffer = m_Data.StartOfDataPointer;

		m_Data.StartOfIndicesPointer = new U32[MAX_INDCS];
		m_Data.IndicesBuffer = m_Data.StartOfIndicesPointer;

		// // 0, 1, 2
		// // 2, 3, 0

		U32 value{};
		for (U32 i{}; i < MAX_INDCS; i += 6) {
		    *(m_Data.IndicesBuffer++) = value;
			*(m_Data.IndicesBuffer++) = value + 1;
			*(m_Data.IndicesBuffer++) = value + 2;

			*(m_Data.IndicesBuffer++) = value + 2;
			*(m_Data.IndicesBuffer++) = value + 3;
			*(m_Data.IndicesBuffer++) = value;

			value += 4;
		}
	}

	void OpenGLrenderer::Beginframe() {
		m_Data.VertexDataBuffer = m_Data.StartOfDataPointer; // reset data buffer pointer to initial buffer start pos
		m_Data.IndexCount = 0;
		m_Data.VertexCount = 0;
	}

	void OpenGLrenderer::Submitquad(const VEC3& a_Position, const VEC3& a_Size, const VEC3& a_Color) {
	    *(m_Data.VertexDataBuffer++) = {VEC3(a_Position.x, a_Position.y + a_Size.y, 0.0f), a_Color/255.0f};
	    *(m_Data.VertexDataBuffer++) = {VEC3(a_Position.x + a_Size.x, a_Position.y + a_Size.y, 0.0f), a_Color/255.0f};
	    *(m_Data.VertexDataBuffer++) = {VEC3(a_Position.x + a_Size.x, a_Position.y, 0.0f), a_Color/255.0f};
	    *(m_Data.VertexDataBuffer++) = {VEC3(a_Position.x, a_Position.y, 0.0f), a_Color/255.0f};

		m_Data.VertexCount += 4;
		m_Data.IndexCount += 6;

	}

	void OpenGLrenderer::Assembleframe() {

	}

	void OpenGLrenderer::Endframe() {
        m_Data.VAO->Bind();
        m_Data.VBO->SetData(m_Data.StartOfDataPointer, sizeof(QuadData) * m_Data.VertexCount);

        m_Data.IBO->SetData(m_Data.StartOfIndicesPointer, m_Data.IndexCount * sizeof(U32));

        glDrawElements(GL_TRIANGLES, m_Data.IndexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLrenderer::Shutdown() {
		if (m_Data.StartOfDataPointer != nullptr)
			delete[] m_Data.StartOfDataPointer;

		if (m_Data.StartOfIndicesPointer != nullptr)
			delete[] m_Data.StartOfIndicesPointer;
	}
}
