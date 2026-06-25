#include "Engine/Window/Window.h"
#include <GLFW/glfw3.h>

#include "Engine/Core/Log.h"
#include "Core/Assert.h"

namespace Frisk::Graphics {

	struct Window::Impl {
		GLFWwindow* window = nullptr;
		U32 width = 0;
		U32 height = 0;
		STRING title;

		~Impl() {
			if (window) {
				glfwDestroyWindow(window);
			}
		}
	};

	Window::Window(U32 a_Width, U32 a_Height, STRING a_Title) {
		m_Impl = std::make_unique<Impl>();

		m_Impl->width = a_Width;
		m_Impl->height = a_Height;
		m_Impl->title = a_Title;

	}

	bool Window::Init() {
		if (m_Impl->window) {
			Log::Warn("window already initialised");
			return true;
		}

		m_Impl->window = glfwCreateWindow(m_Impl->width, m_Impl->height, m_Impl->title.c_str(), nullptr, nullptr);
		if (!m_Impl->window) return false;
		return true;
	}

	bool Window::ShouldClose() const { 
		if (!m_Impl || !m_Impl->window) return true;
		return glfwWindowShouldClose(m_Impl->window);
	}

}