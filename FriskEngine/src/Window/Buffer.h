#pragma once

namespace Frisk {

	enum class VertexDataType : U8 {
		None = static_cast<U8>(0), Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};


	static U32 GetSizeFromDataType(VertexDataType a_Type) {

		U32 base_size = 4;

		switch (a_Type) {
			case VertexDataType::None: return 0;

			case VertexDataType::Float:  return base_size;
			case VertexDataType::Float2: return base_size * 2;
			case VertexDataType::Float3: return base_size * 3;
			case VertexDataType::Float4: return base_size * 4;

			case VertexDataType::Mat3: return base_size * 3 * 3;
			case VertexDataType::Mat4: return base_size * 4 * 4;

			case VertexDataType::Int:  return base_size;
			case VertexDataType::Int2: return base_size * 2;
			case VertexDataType::Int3: return base_size * 3;
			case VertexDataType::Int4: return base_size * 4;
			case VertexDataType::Bool: return 1;
		}
	}

	struct VertexBufferComponent {
		STRING name;
		VertexDataType type;
		U32 size;
		U32 offset;
		bool normalised;

		VertexBufferComponent(const STRING& a_Name, VertexDataType a_Type, bool a_Normalised = false) : name(a_Name), type(a_Type), size(GetSizeFromDataType(a_Type)), normalised(a_Normalised), offset(0) {

		}

		U32 GetInternalComponentCount() const {
    		switch (type) {
    			case VertexDataType::None: return 0;

    			case VertexDataType::Float:  return 1;
    			case VertexDataType::Float2: return 2;
    			case VertexDataType::Float3: return 3;
    			case VertexDataType::Float4: return 4;

    			case VertexDataType::Mat3: return 3;
    			case VertexDataType::Mat4: return 4;

    			case VertexDataType::Int:  return 1;
    			case VertexDataType::Int2: return 2;
    			case VertexDataType::Int3: return 3;
    			case VertexDataType::Int4: return 4;
    			case VertexDataType::Bool: return 1;
    		}
            return 0;
		}
	};

	struct VertexBufferLayout {

        VertexBufferLayout() {}
		VertexBufferLayout(std::initializer_list<VertexBufferComponent> a_List) : m_ComponentList(a_List) {
            DeduceStrideAndOffsets();
		}

	U32 GetStride() const {
	    return m_Stride;
	};

	const std::vector<VertexBufferComponent>& GetComponentList() const {
	    return m_ComponentList;
	}

	private:
	    void DeduceStrideAndOffsets() {
			m_Stride = 0;
			U32 current_offset = 0;

			for (auto& comp : m_ComponentList) {
                m_Stride += comp.size;
                comp.offset = current_offset;

                current_offset += comp.size;
			}
		}

	    U32 m_Stride;
		std::vector<VertexBufferComponent> m_ComponentList;
	};

	class VertexBuffer {
	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* a_Data, U32 a_Size) = 0;

		virtual void SetLayout(const VertexBufferLayout& a_Layout) = 0;
		const virtual VertexBufferLayout& GetLayout() const  = 0;
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
