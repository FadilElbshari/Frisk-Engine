#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "InputManager/InputManager.h"
#include "Window/Shader.h"
#include "Window/Window.h"

#include "Engine/Renderer/Renderer.h"
#include "glm/ext/matrix_transform.hpp"

namespace Frisk
{
    Application::Application(const ApplicationProps &a_BuildProps)
    {

        int status = glfwInit();
        FRISK_ASSERT(status, "failed to initialse GLFW");

        m_Window = std::make_unique<Graphics::Window>(a_BuildProps.width, a_BuildProps.height, a_BuildProps.title);

        m_Window->Init();
        m_Window->SetWindowBackGround(a_BuildProps.background.x, a_BuildProps.background.y, a_BuildProps.background.z);

        m_InputManager = std::make_unique<Input::InputManager>();
    }

    Application::~Application() = default;

    void Application::Run()
    {

        std::unique_ptr<Renderer> renderer = Renderer::CreateI();
        // std::unique_ptr<Shader> shader = Shader::Create("shaders/main.vert", "shaders/main.frag");
        std::unique_ptr<Shader> shader = Shader::Create("shaders/main2.vert", "shaders/main2.frag");

        renderer->Init();

        m_Window->Enable3D();

        MAT4 view = MAT4(1.0f);
        view = glm::rotate(view, glm::radians(45.0f), VEC3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(32.0f), VEC3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, VEC3(-640.0f, -360.0f, 0.0f));

        shader->SetMat4("proj_matrix",
                        glm::ortho(0.0f, static_cast<float>(1280), static_cast<float>(720), 0.0f, -2000.0f, 2000.0f));
        shader->SetMat4("view_matrix", view);

        while (!m_Window->ShouldClose())
        {

            // reading and consuming events
            auto &events = m_Window->GetEventQueue();
            for (auto &e : events)
            {
                m_InputManager->ConsumeEvent(e);
            }
            // clearing the screen before a re-draw
            m_Window->ClearColorBufferBit();

            // if (m_InputManager->GetKeyStatus(GLFW_KEY_R) == Input::KeyStatus::JustPressed) {
            // 	shader->Reload();
            // 	shader->SetMat4("proj_matrix", glm::ortho(0.0f, static_cast<float>(1280), static_cast<float>(720), 0.0f,
            // -1.0f, 1.0f));

            // }

            // drawing stuff
            shader->Bind();
            renderer->Beginframe();

            for (U32 i{}; i < 128; i++)
            {
                for (U32 j{}; j < 72; j++)
                {
                    renderer->Submitquad(VEC3(i * 10, j * 10, 0), VEC3(10, 10, 0),
                                         VEC3((i * j) % 256, (i + j) % 256, (int)abs((long double)(i - j)) % 256));
                }
            }

            renderer->Endframe();
            // OnUpdate();

            // window/input-manager clearing functions
            m_InputManager->HaltInputs();
            m_Window->ClearEventQueue();
            m_Window->SwapBuffers();
            m_Window->PollEvents();
        }

        renderer->Shutdown();
    }
} // namespace Frisk
