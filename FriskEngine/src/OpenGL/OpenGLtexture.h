#pragma once

#include "Window/Texture.h"

namespace Frisk {
    class OpenGLtexture : public Texture {
    public:
        OpenGLtexture();
        OpenGLtexture(const std::filesystem::path& a_TexturePath);
        virtual ~OpenGLtexture() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        U32 m_TextureID;

        U32 m_Width;
        U32 m_Height;

        std::filesystem::path m_TexturePath;
    };
}
