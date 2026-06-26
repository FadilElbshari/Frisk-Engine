#include "OpenGLcontext.h"
#include "Core/Assert.h"


namespace Frisk::Graphics {
	OpenGLcontext::OpenGLcontext(GLFWwindow* a_WindowHandle) : m_WindowHandle(a_WindowHandle) {
		// this implementation assumes that glfwInit() has been called and succeeded.
		FRISK_ASSERT(a_WindowHandle, "invalid window handle");
	}

	bool OpenGLcontext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Log::Error("failed to initialise glad");
			return false;
		}

		Log::Info("Starting GLFW: ", glfwGetVersionString(), "\n");
		Log::Info("Renderer: ", glGetString(GL_RENDERER), "\n");
		Log::Info("OpenGL Version: ", glGetString(GL_VERSION), "\n\n");
	}

	void OpenGLcontext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}