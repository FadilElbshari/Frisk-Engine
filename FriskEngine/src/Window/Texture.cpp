#include "Window/Texture.h"
#include "OpenGL/OpenGLtexture.h"

namespace Frisk {
    std::unique_ptr<Texture> Texture::Create() {
        // only opengl for now
        return std::make_unique<OpenGLtexture>();
    }

    std::unique_ptr<Texture> Texture::Create(const std::filesystem::path& a_TexturePath) {
        // only opengl for now
        return std::make_unique<OpenGLtexture>(a_TexturePath);
    }
}
