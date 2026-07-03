#include "OpenGL/OpenGLrenderer.h"

namespace Frisk {

	OpenGLrenderer::~OpenGLrenderer() {

	}
	
	void OpenGLrenderer::Init() {
		m_Data->VAO = VertexArray::Create();
		m_Data->VBO = VertexBuffer::Create(sizeof(QuadData) * MAX_VERTS);
		m_Data->VBO->SetLayout(VertexBufferLayout({ VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3) }));

		m_Data->IBO = IndexBuffer::Create(sizeof(U32) * MAX_INDCS);

		m_Data->VertexDataBuffer = new QuadData[MAX_VERTS];
		m_Data->StartOfDataPointer = m_Data->VertexDataBuffer;

		m_Data->IndicesBuffer = new U32[MAX_INDCS];
		m_Data->StartOfIndicesPointer = m_Data->IndicesBuffer;
	}

	void OpenGLrenderer::Beginframe() {
		m_Data->VertexDataBuffer = m_Data->StartOfDataPointer; // reset data buffer pointer to initial buffer start pos
		m_Data->IndicesBuffer = m_Data->StartOfIndicesPointer;
	}

	void OpenGLrenderer::Submitquad(const VEC3& a_Position, const VEC3& a_Size, const VEC3& a_Color) {

	}

	void OpenGLrenderer::Assembleframe() {

	}

	void OpenGLrenderer::Endframe() {

	}

	void OpenGLrenderer::Shutdown() {
		m_Data->VertexDataBuffer = m_Data->StartOfDataPointer; // reset data buffer pointer to initial buffer start pos
		m_Data->IndicesBuffer = m_Data->StartOfIndicesPointer;

		if (m_Data->VertexDataBuffer != nullptr)
			delete[] m_Data->VertexDataBuffer;

		if (m_Data->IndicesBuffer != nullptr)
			delete[] m_Data->IndicesBuffer;
	}
}