#include "OpenGL/OpenGLshader.h"

#include "Engine/Utils/File.h"
#include "Engine/Core/Log.h"

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


    U32 OpenGLshader::GetUniformLocation(STRING& a_Name) const {
        return glGetUniformLocation(m_ShaderProgram, a_Name.c_str());
    }
}
