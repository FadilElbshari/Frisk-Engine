#pragma once

#include "Window/Shader.h"

namespace Frisk {
    class OpenGLshader : public Shader {
        public:
            OpenGLshader(const std::filesystem::path& a_VertexShaderPath, const std::filesystem::path& a_FragmentShaderPath);
            virtual ~OpenGLshader();

            virtual void Bind() const override;
            virtual void Unbind() const override;


        private:
            U32 m_VertexShader;
            U32 m_FragmentShader;
            U32 m_ShaderProgram;

            U32 GetUniformLocation(STRING& a_Name) const;

    };
}
