#include "Window/GraphicsContext.h"
#include "OpenGL/OpenGLcontext.h"

#include "Core/Assert.h"

namespace Frisk::Graphics
{
    std::unique_ptr<GraphicsContext> GraphicsContext::Create(GLFWwindow *a_WindowHandle)
    {
        // for now only opengl is supported so...
        FRISK_ASSERT(a_WindowHandle, "invadid window handle");
        return std::make_unique<OpenGLcontext>(a_WindowHandle);
    }
} // namespace Frisk::Graphics
