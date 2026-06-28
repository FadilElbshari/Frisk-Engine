#pragma once

namespace Frisk {
	class VertexBuffer {
	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* a_Data, U32 a_Size) = 0;

		// size in bytes
		static std::unique_ptr<VertexBuffer> Create(const void* a_Verts, U32 a_Size); // for STATIC_DRAW: this will be mainly used for instanced drawing
		static std::unique_ptr<VertexBuffer> Create(U32 a_Size); // for DYNAMIC_DRAW
	};

	class IndexBuffer {
	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const U32* a_Data, U32 a_Size) = 0;

		// size in bytes
		static std::unique_ptr<IndexBuffer> Create(const U32* a_Indcs, U32 a_Size);
		static std::unique_ptr<IndexBuffer> Create(U32 a_Size);
	};
}
