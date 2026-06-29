#include "Window/Shader.h"
#include "OpenGL/OpenGLshader.h"
#include <memory>

namespace Frisk {
    std::unique_ptr<Shader> Shader::Create(std::filesystem::path &a_VertexShaderPath, std::filesystem::path &a_FragmentShaderPath) {
        // only opengl for now
        return std::make_unique<OpenGLshader>(a_VertexShaderPath, a_FragmentShaderPath);
    }
}
