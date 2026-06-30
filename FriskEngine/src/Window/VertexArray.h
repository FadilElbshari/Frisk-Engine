#pragma once

#include "Window/Buffer.h"

namespace Frisk {
	class VertexArray {
	public:

		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AssignVertexBuffer(std::unique_ptr<VertexBuffer>& a_VBO) = 0;

		static std::unique_ptr<VertexArray> Create();
	};
}
