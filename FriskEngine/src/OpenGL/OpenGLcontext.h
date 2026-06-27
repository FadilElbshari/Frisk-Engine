#pragma once
#include <GLFW/glfw3.h>

#include "Window/GraphicsContext.h"

namespace Frisk::Graphics {
	class OpenGLcontext : public GraphicsContext {
	public:
		OpenGLcontext(GLFWwindow* a_WindowHandle);
		~OpenGLcontext() override = default;

		virtual bool Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};
}