#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "Window/Buffer.h"
#include "Window/Window.h"
#include "InputManager/InputManager.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Window/VertexArray.h"
#include "Window/Shader.h"

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
				320.0f, 180.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				960.0f, 180.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				960.0f, 540.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				320.0f, 540.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		U32 indcs[] = {
			0, 1, 2,
			2, 3, 0
		};

	    std::unique_ptr<Shader> shader = Shader::Create("shaders/main.vert", "shaders/main.frag");
		std::unique_ptr<VertexArray> VAO = VertexArray::Create();


		std::unique_ptr<VertexBuffer> VBO = VertexBuffer::Create(verts, sizeof(verts));
		std::shared_ptr<IndexBuffer> IBO = IndexBuffer::Create(indcs, sizeof(indcs));

		VBO->SetLayout(VertexBufferLayout({ VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3) }));

		VAO->AssignVertexBuffer(VBO);
		VAO->AssignIndexBuffer(IBO);

		m_Window->Enable3D();

		shader->SetMat4("proj_matrix", glm::ortho(0.0f, static_cast<float>(1280), 0.0f, static_cast<float>(720), -1.0f, 1.0f));

		while (!m_Window->ShouldClose()) {

			// reading and consuming events
			auto& events = m_Window->GetEventQueue();
			for (auto& e : events) {
				m_InputManager->ConsumeEvent(e);
			}
			// clearing the screen before a re-draw
			m_Window->ClearColorBufferBit();

			if (m_InputManager->GetKeyStatus(GLFW_KEY_R) == Input::KeyStatus::JustPressed) {
				shader->Reload();
			}

			// drawing stuff
			shader->Bind();
			VAO->Bind();
			//shader->SetFloat("time", glfwGetTime());
			glDrawElements(GL_TRIANGLES, VAO->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

			//OnUpdate();


			// window/input-manager clearing functions
			m_InputManager->HaltInputs();
			m_Window->ClearEventQueue();
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}
}
