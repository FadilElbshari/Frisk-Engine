#include "Window/Window.h"
#include <GLFW/glfw3.h>

#include "Engine/Core/Log.h"
#include "Core/Assert.h"

namespace Frisk::Graphics {


	Window::Window(U32 a_Width, U32 a_Height, STRING a_Title) : m_Width(a_Width), m_Height(a_Height), m_Title(a_Title) {}

	Window::~Window() {
	    if (m_WindowHandle) glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    };

	bool Window::Init() {
		if (m_WindowHandle) {
			Log::Warn("window already initialised");
			return true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_WindowHandle = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!m_WindowHandle) return false;

		m_Context = GraphicsContext::Create(m_WindowHandle);
		if (!m_Context) return false;
		if (!m_Context->Init()) return false;

		m_Running = true;

		glfwSetWindowUserPointer(m_WindowHandle, this);

		glViewport(0, 0, m_Width, m_Height);

		// implement callbacks
		glfwSetErrorCallback([](int error, CNST_CHR_PTR description) {
			Log::Error("GLFW Error: ", error, ", ", description, "\n\n");
		});

		glfwSetFramebufferSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height) {
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (!win) return;

			win->m_Width = width;
			win->m_Height = height;


			glViewport(0, 0, width, height);
		});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    		auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    		if (!win) return;

			win->m_EventQueue.push_back(KeyEvent{ key, scancode, action, mods });
		});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods) {
    		auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    		if (!win) return;

			win->m_EventQueue.push_back(MouseButtonEvent{ button, action, mods });
		});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double x, double y) {
    		auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    		if (!win) return;

			//impl->event_queue.push_back(MouseMoveEvent{ x, y });
		});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window) {
    		auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    		if (!win) return;

            win->m_Running = false;
		});

		return true;
	}

	bool Window::ShouldClose() const {
		return !m_Running;
	}

	void Window::SwapBuffers() const {
		FRISK_ASSERT(m_Context, "invalid context");
		m_Context->SwapBuffers();
	}

	void Window::PollEvents() const {
        glfwPollEvents();
	}

	void Window::SetWindowBackGround(float r, float g, float b) const {
		glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	void Window::ClearColorBufferBit() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	const std::vector<Event>& Window::GetEventQueue() const {
		return m_EventQueue;
	}

	void Window::ClearEventQueue() {
	    m_EventQueue.clear();
	}


}
