#pragma once

#include "Window/VertexArray.h"

namespace Frisk
{
    class OpenGLvertexArray : public VertexArray
    {
      public:
        OpenGLvertexArray();
        virtual ~OpenGLvertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AssignVertexBuffer(std::unique_ptr<VertexBuffer> &a_VBO) override;

        virtual void AssignIndexBuffer(std::shared_ptr<IndexBuffer> a_IBO) override;

        U32 GetIndexCount() const override;

      private:
        U32 m_VertexArrayID;
        U32 m_VertexAttribCounter;

        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
} // namespace Frisk
