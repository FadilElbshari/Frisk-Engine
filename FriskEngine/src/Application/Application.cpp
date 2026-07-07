#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "InputManager/InputManager.h"
#include "Window/Shader.h"

#include "Window/Buffer.h"
#include "Window/VertexArray.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_transform.hpp"


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
};

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
		m_Window->Enable3D();

		m_InputManager = std::make_unique<Input::InputManager>();
	}

	Application::~Application() = default;

	void Application::Run() {
	    std::unique_ptr<Shader> shader = Shader::Create("shaders/main.vert", "shaders/main.frag");

		std::unique_ptr<VertexArray> VAO1 = VertexArray::Create();
		std::unique_ptr<VertexBuffer> VBO1 = VertexBuffer::Create(vertices, sizeof(vertices));
		VBO1->SetLayout(VertexBufferLayout({VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3)}));
		VAO1->AssignVertexBuffer(VBO1);

		std::unique_ptr<VertexArray> VAO2 = VertexArray::Create();
		std::unique_ptr<VertexBuffer> VBO2 = VertexBuffer::Create(vertices, sizeof(vertices));
		VBO2->SetLayout(VertexBufferLayout({VertexBufferComponent("Position", VertexDataType::Float3), VertexBufferComponent("Color", VertexDataType::Float3)}));
		VAO2->AssignVertexBuffer(VBO2);

		MAT4 view = MAT4(1.0f);
		MAT4 proj = MAT4(1.0f);
		MAT4 model = MAT4(1.0f);

		shader->SetMat4("view_matrix", view);
		shader->SetMat4("proj_matrix", proj);

		model = glm::rotate(model, glm::radians(45.0f), VEC3(-1.0f, 1.0f, 0.0f));
		shader->SetMat4("model_matrix", model);

		while (!m_Window->ShouldClose()) {

			// reading and consuming events
			auto& events = m_Window->GetEventQueue();
			for (auto& e : events) {
				m_InputManager->ConsumeEvent(e);
			}
			// clearing the screen before a re-draw
			m_Window->ClearColorBufferBit();

			shader->Bind();
			VAO1->Bind();

			glDrawArrays(GL_TRIANGLES, 0, 36);

			// window/input-manager clearing functions
			m_InputManager->HaltInputs();
			m_Window->ClearEventQueue();
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}
}
