#include "Window/Window.h"
#include <GLFW/glfw3.h>

#include "Engine/Core/Log.h"
#include "Core/Assert.h"

#include "GraphicsContext.h"

namespace Frisk::Graphics {

	struct Window::Impl {
		GLFWwindow* window = nullptr;
		std::unique_ptr<GraphicsContext> context;

		std::vector<Event> event_queue;

		U32 width = 0;
		U32 height = 0;
		STRING title;

		~Impl() {
			context.reset();
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

	Window::~Window() = default;

	bool Window::Init() {
		if (m_Impl->window) {
			Log::Warn("window already initialised");
			return true;
		}

		m_Impl->window = glfwCreateWindow(m_Impl->width, m_Impl->height, m_Impl->title.c_str(), nullptr, nullptr);
		if (!m_Impl->window) return false;

		m_Impl->context = GraphicsContext::Create(m_Impl->window);
		if (!m_Impl->context) return false;
		if (!m_Impl->context->Init()) return false;

		glfwSetWindowUserPointer(m_Impl->window, m_Impl.get());

		glViewport(0, 0, m_Impl->width, m_Impl->height);

		// implement callbacks
		glfwSetErrorCallback([](int error, CNST_CHR_PTR description) {
			Log::Error("GLFW Error: ", error, ", ", description, "\n\n");
		});

		glfwSetFramebufferSizeCallback(m_Impl->window, [](GLFWwindow* window, int width, int height) {
			auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(window));
			if (!impl) return;

			impl->width = width;
			impl->height = height;

			glViewport(0, 0, width, height);
		});

		glfwSetKeyCallback(m_Impl->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(window));
			if (!impl) return;

			impl->event_queue.push_back(KeyEvent{ key, scancode, action, mods });
		});

		glfwSetMouseButtonCallback(m_Impl->window, [](GLFWwindow* window, int button, int action, int mods) {
			auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(window));
			if (!impl) return;

			impl->event_queue.push_back(MouseButtonEvent{ button, action, mods });
		});

		glfwSetCursorPosCallback(m_Impl->window, [](GLFWwindow* window, double x, double y) {
			auto* impl = static_cast<Impl*>(glfwGetWindowUserPointer(window));
			if (!impl) return;

			//impl->event_queue.push_back(MouseMoveEvent{ x, y });
		});

		return true;
	}

	bool Window::ShouldClose() const { 
		if (!m_Impl || !m_Impl->window) return true;
		return glfwWindowShouldClose(m_Impl->window);
	}

	void Window::SwapBuffers() const {
		FRISK_ASSERT(m_Impl && m_Impl->context, "invalid context");
		m_Impl->context->SwapBuffers();
	}

	const std::vector<Event>& Window::GetEventQueue() const {
		return m_Impl->event_queue;
	}

	void Window::ClearEventQueue() { m_Impl->event_queue.clear(); }


}