#include "Engine/Renderer/Renderer.h"
#include "Window/VertexArray.h"
#include "Window/Buffer.h"

#define MAX_QUADS 100
#define MAX_VERTS MAX_QUADS * 4
#define MAX_INDCS MAX_QUADS * 6

namespace Frisk {

	struct QuadData {
		VEC3 position;
		VEC3 color;
	};

	class OpenGLrenderer : public Renderer {
	public:
		OpenGLrenderer() = default;

		virtual ~OpenGLrenderer();

		virtual void Init() override;

		virtual void Beginframe() override;
		virtual void Assembleframe() override;
		virtual void Endframe() override;

		virtual void Submitquad(const VEC3& a_Position, const VEC3& a_Size, const VEC3& a_Color) override;

		virtual void Shutdown() override;

	private:
		struct RendererData {
			std::unique_ptr<VertexArray> VAO;

			std::unique_ptr<VertexBuffer> VBO;
			std::shared_ptr<IndexBuffer> IBO;

			QuadData* VertexDataBuffer = nullptr;
			QuadData* StartOfDataPointer = nullptr;

			U32* IndicesBuffer = nullptr;
			U32* StartOfIndicesPointer = nullptr;

			U32 VertexCount = 0;
			U32 IndexCount = 0;

		};

		RendererData m_Data;
	};
}
