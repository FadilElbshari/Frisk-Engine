#pragma once
#include <GLFW/glfw3.h>

namespace Frisk::Graphics {
	class OpenGLcontext {
	public:
		OpenGLcontext(GLFWwindow* a_WindowHandle);
		~OpenGLcontext() = default;

		bool Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;

	};
}