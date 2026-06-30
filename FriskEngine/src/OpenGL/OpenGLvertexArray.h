#pragma once

#include "Window/VertexArray.h"

namespace Frisk {
    class OpenGLvertexArray : public VertexArray {
    public:
        OpenGLvertexArray();
        virtual ~OpenGLvertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AssignVertexBuffer(std::unique_ptr<VertexBuffer>& a_VBO) override;

    private:
        U32 m_VertexArrayID;
        U32 m_VertexAttribCounter;

    };
}
