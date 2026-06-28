#include "Window/Buffer.h"

namespace Frisk {
    class OpenGLvertexBuffer : public VertexBuffer {
    public:

        OpenGLvertexBuffer(const void* a_Verts, U32 a_Size);
        OpenGLvertexBuffer(U32 a_Size);

        virtual ~OpenGLvertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        U32 m_VertexBufferID;
    };

    class OpenGLindexBuffer : public IndexBuffer {
    public:
        OpenGLindexBuffer(const U32* a_Verts, U32 a_Size);
        OpenGLindexBuffer(U32 a_Size);

        virtual ~OpenGLindexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        U32 m_IndexBufferID;
    };
}
