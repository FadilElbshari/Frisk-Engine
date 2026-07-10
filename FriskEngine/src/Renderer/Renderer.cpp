#include "Engine/Renderer/Renderer.h"
#include "OpenGL/OpenGLrendererBatched.h"
#include "OpenGL/OpenGLrendererInstanced.h"

namespace Frisk
{
    std::unique_ptr<Renderer> Renderer::CreateBatched()
    {
        // OpenGL for now
        return std::make_unique<OpenGLrendererBatched>();
    }

    std::unique_ptr<Renderer> Renderer::CreateInstanced()
    {
        // OpenGL for now
        return std::make_unique<OpenGLrendererInstanced>();
    }
} // namespace Frisk
