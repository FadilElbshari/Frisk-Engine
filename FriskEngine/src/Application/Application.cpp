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
		m_Window->SetWindowBackGround(a_BuildProps.background.x, a_BuildProps.background.y, a_BuildProps.background.z);

		m_InputManager = std::make_unique<Input::InputManager>();
	}

	Application::~Application() = default;

	void Application::Run() {
		while (!m_Window->ShouldClose()) {

			auto& events = m_Window->GetEventQueue();
			for (auto& e : events) {
				m_InputManager->ConsumeEvent(e);
			}

			OnUpdate();


			m_Window->ClearEventQueue();
			
			m_Window->ClearColorBufferBit();
			m_Window->SwapBuffers();

			m_Window->PollEvents();
		}
	}
}
