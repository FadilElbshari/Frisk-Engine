#pragma once
#include <GLFW/glfw3.h>

namespace Frisk::Graphics
{
    class GraphicsContext
    {
      public:
        GraphicsContext() = default;
        virtual ~GraphicsContext() = default;

        virtual bool Init() = 0;
        virtual void SwapBuffers() = 0;

        static std::unique_ptr<GraphicsContext> Create(GLFWwindow *a_WindowHandle);
    };
} // namespace Frisk::Graphics