#pragma once

namespace Frisk {

	enum class PossibleDataType : U8 {
		None = static_cast<U8>(0), Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4
	};


	static U32 GetSizeFromDataType(PossibleDataType a_Type) {

		U32 base_size = 4;

		switch (a_Type) {
			case PossibleDataType::None: return 0;

			case PossibleDataType::Float:  return base_size;
			case PossibleDataType::Float2: return base_size * 2;
			case PossibleDataType::Float3: return base_size * 3;
			case PossibleDataType::Float4: return base_size * 4;

			case PossibleDataType::Int:  return base_size;
			case PossibleDataType::Int2: return base_size * 2;
			case PossibleDataType::Int3: return base_size * 3;
			case PossibleDataType::Int4: return base_size * 4;

			case PossibleDataType::Mat3: return base_size * 4 * 3;
			case PossibleDataType::Mat4: return base_size * 4 * 4;
		}
	}

	struct VertexBufferComponent {
		STRING name;
		PossibleDataType type;
		U32 size;
		bool normalised;

		VertexBufferComponent(STRING& a_Name, PossibleDataType a_Type, bool a_Normalised = false) : name(a_Name), type(a_Type), size(GetSizeFromDataType(a_Type)), normalised(a_Normalised) {

		}
	};

	struct VertexBufferLayout {
		VertexBufferLayout(std::initializer_list<VertexBufferComponent> a_List) : m_ComponentList(a_List) {

		}


	private:
		std::vector<VertexBufferComponent> m_ComponentList;
	};

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
		virtual U32 GetIndexCount() const = 0;

		// size in bytes
		static std::unique_ptr<IndexBuffer> Create(const U32* a_Indcs, U32 a_Size);
		static std::unique_ptr<IndexBuffer> Create(U32 a_Size);
	};
}
