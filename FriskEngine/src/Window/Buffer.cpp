#include "Window/Buffer.h"
#include "OpenGL/OpenGLbuffer.h"

#include "Core/Assert.h"

namespace Frisk
{
    std::unique_ptr<VertexBuffer> VertexBuffer::Create(const void *a_Verts, U32 a_Size)
    {
        // some logic to determine which API is being used
        FRISK_ASSERT(a_Verts, "invalid verts pointer");
        return std::make_unique<OpenGLvertexBuffer>(a_Verts, a_Size);
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(U32 a_Size)
    {
        // some logic to determine which API is being used
        return std::make_unique<OpenGLvertexBuffer>(a_Size);
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const U32 *a_Indcs, U32 a_Size)
    {
        // some logic to determine which API is being used
        FRISK_ASSERT(a_Indcs, "invalid verts pointer");
        return std::make_shared<OpenGLindexBuffer>(a_Indcs, a_Size);
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(U32 a_Size)
    {
        // some logic to determine which API is being used
        return std::make_shared<OpenGLindexBuffer>(a_Size);
    }
} // namespace Frisk
