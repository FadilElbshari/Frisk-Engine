#include "Window/Shader.h"
#include "OpenGL/OpenGLshader.h"

namespace Frisk {
    std::unique_ptr<Shader> Shader::Create(const std::filesystem::path &a_VertexShaderPath, const std::filesystem::path &a_FragmentShaderPath) {
        // only opengl for now
        return std::make_unique<OpenGLshader>(a_VertexShaderPath, a_FragmentShaderPath);
    }
}
