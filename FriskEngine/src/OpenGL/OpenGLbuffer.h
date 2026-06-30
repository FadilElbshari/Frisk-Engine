#include "Window/Buffer.h"

namespace Frisk {
    class OpenGLvertexBuffer : public VertexBuffer {
    public:

        OpenGLvertexBuffer(const void* a_Verts, U32 a_Size);
        OpenGLvertexBuffer(U32 a_Size);

        virtual ~OpenGLvertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const void* a_Data, U32 a_Size) override;

        virtual void SetLayout(const VertexBufferLayout& a_Layout) override;
        const virtual VertexBufferLayout& GetLayout() const override;

    private:
        U32 m_VertexBufferID;
        VertexBufferLayout m_Layout;
    };

    class OpenGLindexBuffer : public IndexBuffer {
    public:
        OpenGLindexBuffer(const U32* a_Verts, U32 a_Size);
        OpenGLindexBuffer(U32 a_Size);

        virtual ~OpenGLindexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const U32* a_Data, U32 a_Size) override;
        virtual U32 GetIndexCount() const override;

    private:
        U32 m_IndexBufferID;
        U32 m_IndexCount;
    };
}
