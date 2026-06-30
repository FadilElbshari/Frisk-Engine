#include "OpenGL/OpenGLshader.h"

#include "Engine/Utils/File.h"
#include "Engine/Core/Log.h"
#include "pch.h"

namespace Frisk {

    OpenGLshader::OpenGLshader(const std::filesystem::path &a_VertexShaderPath, const std::filesystem::path &a_FragmentShaderPath) {
        STRING Vsource = ParseFile(a_VertexShaderPath);
        STRING Fsource = ParseFile(a_FragmentShaderPath);

        if (!strcmp(Vsource.c_str(), "") || !strcmp(Fsource.c_str(), "")) {
            Log::Error("missing file contents\n");
            return;
        }

        CNST_CHR_PTR Vcode = Vsource.c_str();
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertexShader, 1, &Vcode, NULL);
        glCompileShader(m_VertexShader);

        int success;
        char info[512];

        glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_VertexShader, 512, NULL, info);
            Log::Error("Error compiling vertex shader: ", a_VertexShaderPath, ". ", info, "\n\n");
            return;
        }

        CNST_CHR_PTR Fcode = Fsource.c_str();
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_FragmentShader, 1, &Fcode, NULL);
        glCompileShader(m_FragmentShader);

        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_FragmentShader, 512, NULL, info);
            Log::Error("Error compiling vertex shader: ", a_FragmentShaderPath, ". ", info, "\n\n");
            return;
        }

        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, m_VertexShader);
        glAttachShader(m_ShaderProgram, m_FragmentShader);
        glLinkProgram(m_ShaderProgram);

        Log::Info("shader program successfully compiled\n");
    }

    OpenGLshader::~OpenGLshader() {
        glDeleteProgram(m_ShaderProgram);

        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);
    }


    void OpenGLshader::Bind() const {
        glUseProgram(m_ShaderProgram);
    }

    void OpenGLshader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLshader::SetFloat(const STRING& a_Name, float a_Value) const {
        Bind();
        glUniform1f(GetUniformLocation(a_Name), a_Value);
    }
    void OpenGLshader::SetFloat2(const STRING& a_Name, const VEC2& a_Value) const {
        Bind();
        glUniform2f(GetUniformLocation(a_Name), a_Value.x, a_Value.y);
    }
    void OpenGLshader::SetFloat3(const STRING& a_Name, const VEC3& a_Value) const {
        Bind();
        glUniform3f(GetUniformLocation(a_Name), a_Value.x, a_Value.y, a_Value.z);
    }
    void OpenGLshader::SetFloat4(const STRING& a_Name, const VEC4& a_Value) const {
        Bind();
        glUniform4f(GetUniformLocation(a_Name), a_Value.x, a_Value.y, a_Value.z, a_Value.w);
    }
    void OpenGLshader::SetMat3(const STRING& a_Name, const MAT3& a_Value) const {
        Bind();
        glUniformMatrix3fv(GetUniformLocation(a_Name), 1, GL_FALSE, glm::value_ptr(a_Value));
    }
    void OpenGLshader::SetMat4(const STRING& a_Name, const MAT4& a_Value) const {
        Bind();
        glUniformMatrix4fv(GetUniformLocation(a_Name), 1, GL_FALSE, glm::value_ptr(a_Value));
    }

    void OpenGLshader::SetBool(const STRING& a_Name, bool a_Value) const {
        Bind();
        glUniform1i(GetUniformLocation(a_Name), a_Value);
    }


    U32 OpenGLshader::GetUniformLocation(const STRING& a_Name) const {
        return glGetUniformLocation(m_ShaderProgram, a_Name.c_str());
    }
}
