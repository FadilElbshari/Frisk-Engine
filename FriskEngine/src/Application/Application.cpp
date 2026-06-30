#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "Window/Buffer.h"
#include "Window/Window.h"
#include "InputManager/InputManager.h"

#include <GLFW/glfw3.h>

#include "Window/Buffer.h"
#include "Window/VertexArray.h"
#include "Window/Shader.h"
#include "pch.h"

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

	    float verts[] = {
				-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 	    0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

	    std::unique_ptr<Shader> shader = Shader::Create("shaders/main.vert", "shaders/main.frag");
		std::unique_ptr<VertexArray> VAO = VertexArray::Create();


		std::unique_ptr<VertexBuffer> VBO = VertexBuffer::Create(verts, sizeof(verts));

		VertexBufferLayout layout({VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3)});

		VBO->SetLayout(layout);

		VAO->AssignVertexBuffer(VBO);

		while (!m_Window->ShouldClose()) {

			auto& events = m_Window->GetEventQueue();
			for (auto& e : events) {
				m_InputManager->ConsumeEvent(e);
			}

			m_Window->ClearColorBufferBit();

			if (m_InputManager->GetKeyStatus(GLFW_KEY_R) == Input::KeyStatus::JustPressed) {
				shader->Reload();
			}

			shader->Bind();
			VAO->Bind();
			// glBindVertexArray(VAO);
			shader->SetFloat("time", glfwGetTime());
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//OnUpdate();


			m_InputManager->HaltInputs();

			m_Window->ClearEventQueue();
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}
}
