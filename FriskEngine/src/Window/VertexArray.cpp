#include "Window/VertexArray.h"
#include "OpenGL/OpenGLvertexArray.h"
#include <memory>

namespace Frisk {
    std::unique_ptr<VertexArray> VertexArray::Create() {
        // for now only opengl
        return std::make_unique<OpenGLvertexArray>();
    }
}
