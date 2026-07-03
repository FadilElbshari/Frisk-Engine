#include "OpenGL/OpenGLrenderer.h"

namespace Frisk {

	
	void OpenGLrenderer::Init() {
		m_Data.VAO = VertexArray::Create();
		m_Data.VBO = VertexBuffer::Create(sizeof(QuadData) * MAX_VERTS);

		m_Data.IBO = IndexBuffer::Create(sizeof(U32) * MAX_INDCS);

		m_Data.VertexDataBuffer = new QuadData[MAX_VERTS];
		m_Data.StartOfDataPointer = m_Data.VertexDataBuffer;

		m_Data.IndicesBuffer = new U32[MAX_INDCS];
		m_Data.StartOfIndicesPointer = m_Data.IndicesBuffer;
	}

	void OpenGLrenderer::Beginframe() {
		m_Data.VertexDataBuffer = m_Data.StartOfDataPointer; // reset data buffer pointer to initial buffer start pos
		m_Data.IndicesBuffer = m_Data.StartOfIndicesPointer;
	}

	void OpenGLrenderer::Shutdown() {
		if (m_Data.VertexDataBuffer != nullptr)
			delete[] m_Data.VertexDataBuffer;

		if (m_Data.IndicesBuffer != nullptr)
			delete[] m_Data.IndicesBuffer;
	}
}