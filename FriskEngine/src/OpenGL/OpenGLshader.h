#pragma once

#include "Window/Shader.h"

namespace Frisk {
    class OpenGLshader : public Shader {
        public:
            OpenGLshader(const std::filesystem::path& a_VertexShaderPath, const std::filesystem::path& a_FragmentShaderPath);
            virtual ~OpenGLshader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void SetFloat(const STRING& a_Name, float a_Value) const override;
    		virtual void SetFloat2(const STRING& a_Name, const VEC2& a_Value) const override;
    		virtual void SetFloat3(const STRING& a_Name, const VEC3& a_Value) const override;
    		virtual void SetFloat4(const STRING& a_Name, const VEC4& a_Value) const override;

    		virtual void SetMat3(const STRING& a_Name, const MAT3& a_Value) const override;
            virtual void SetMat4(const STRING& a_Name, const MAT4& a_Value) const override;

    		virtual void SetBool(const STRING& a_Name, bool a_Value) const override;

        private:
            U32 m_VertexShader;
            U32 m_FragmentShader;
            U32 m_ShaderProgram;

            U32 GetUniformLocation(const STRING& a_Name) const;

    };
}
