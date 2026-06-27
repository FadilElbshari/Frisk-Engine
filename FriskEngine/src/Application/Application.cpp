#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "Window/Window.h"
#include "InputManager/InputManager.h"

#include <GLFW/glfw3.h>

namespace Frisk {
	Application::Application(const ApplicationProps& a_BuildProps) {

		int status = glfwInit();
		FRISK_ASSERT(status, "failed to initialse GLFW");

		m_Window = std::make_unique<Graphics::Window>(
			a_BuildProps.width,
			a_BuildProps.height,
			a_BuildProps.title
		);

		m_Window->Init();

		m_InputManager = std::make_unique<Input::InputManager>();
	}

	Application::~Application() = default;

	void Application::Run() {
		Log::Info("Entered run function\n");
		while (!m_Window->ShouldClose()) {

			glfwPollEvents();

			auto& events = m_Window->GetEventQueue();
			auto size = events.size();
			if (size > 0) Log::Info("Event size: ", events.size(), "\n");

			OnUpdate();

			m_Window->ClearEventQueue();
			m_Window->SwapBuffers();
		}
	}
}