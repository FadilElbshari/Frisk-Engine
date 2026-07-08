#pragma once

#include "Window/Buffer.h"

namespace Frisk
{
    class VertexArray
    {
      public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AssignVertexBuffer(std::unique_ptr<VertexBuffer> &a_VBO) = 0;
        virtual void AssignIndexBuffer(std::shared_ptr<IndexBuffer> a_IBO) = 0;

        virtual U32 GetIndexCount() const = 0;

        static std::unique_ptr<VertexArray> Create();
    };
} // namespace Frisk
