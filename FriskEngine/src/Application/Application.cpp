#include "Engine/Application/Application.h"
#include "Core/Assert.h"

#include "GLFW/glfw3.h"
#include "InputManager/InputManager.h"
#include "Physics/Camera.h"
#include "Window/Shader.h"
#include "Window/Window.h"

#include "Window/Buffer.h"
#include "Window/VertexArray.h"
#include "glm/ext/matrix_transform.hpp"
#include <chrono>
#include <memory>
#include <string>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

namespace Frisk
{
    Application::Application(const ApplicationProps &a_BuildProps) : m_Props(a_BuildProps),
        m_Window(std::make_unique<Graphics::Window>(a_BuildProps.width, a_BuildProps.height, a_BuildProps.title)),
        m_InputManager(std::make_unique<Input::InputManager>()),
        m_Camera(std::make_unique<Camera>(VEC3(0.0f, 1.0f, -3.0f), VEC3(0.0f, 0.0f, 0.0f), static_cast<float>(a_BuildProps.width) / a_BuildProps.height, VEC3(45.0f, 0.1f, 1000.0f)))
    {

        int status = glfwInit();
        FRISK_ASSERT(status, "failed to initialse GLFW");

        m_Window->Init();
        m_Window->DisableVSync();
        m_Window->SetWindowBackGround(a_BuildProps.background.x, a_BuildProps.background.y, a_BuildProps.background.z);
        m_Window->Enable3D();
        m_Window->HideCursor();
    }

    Application::~Application() = default;

    void Application::Run()
    {
        std::unique_ptr<Shader> shader = Shader::Create("shaders/main.vert", "shaders/main.frag");

        std::unique_ptr<VertexArray> VAO1 = VertexArray::Create();
        std::unique_ptr<VertexBuffer> VBO1 = VertexBuffer::Create(vertices, sizeof(vertices));
        VBO1->SetLayout(VertexBufferLayout({VertexBufferComponent("Position", VertexDataType::Float3),
            VertexBufferComponent("Normals", VertexDataType::Float3)}));
        VAO1->AssignVertexBuffer(VBO1);

        std::unique_ptr<VertexArray> VAO2 = VertexArray::Create();
        std::unique_ptr<VertexBuffer> VBO2 = VertexBuffer::Create(vertices, sizeof(vertices));
        VBO2->SetLayout(VertexBufferLayout({VertexBufferComponent("Position", VertexDataType::Float3),
            VertexBufferComponent("Normals", VertexDataType::Float3)}));
        VAO2->AssignVertexBuffer(VBO2);

        m_InputManager->setMousePos(m_Window->GetMousePos());

        VEC3 light_pos = {1.2f, 1.0f, 2.0f};

        auto fps_count_time = std::chrono::steady_clock::now();

        float dt = 0;
        while (!m_Window->ShouldClose())
        {
            auto frameStart = std::chrono::steady_clock::now();
            // reading and consuming events
            auto &events = m_Window->GetEventQueue();
            for (auto &e : events)
            {
                m_InputManager->ConsumeEvent(e);
            }
            m_InputManager->setMousePos(m_Window->GetMousePos());
            // clearing the screen before a re-draw
            m_Window->ClearColorBufferBit();


            if (m_InputManager->GetKeyStatus(GLFW_KEY_R) == Input::KeyStatus::JustPressed)
            {
                shader->Reload();
            }


            shader->Bind();
            m_Camera->cameraUpdate(dt, m_InputManager);

            shader->SetMat4("proj_matrix", m_Camera->getProj());
            shader->SetMat4("view_matrix", m_Camera->getView());

            MAT4 model = MAT4(1.0f);
            double time = glfwGetTime();
            // model = glm::translate(model, VEC3(0.0f, static_cast<float>(sin(time)) * 0.01, 0.0f));
            VEC4 res = model * VEC4(light_pos, 1.0f);
            light_pos = VEC3(res);

            shader->SetFloat3("obj_color", {1.0f, 0.0f, 0.0f});
            shader->SetFloat3("light_source", {1.0f, 1.0f, 1.0f});
            shader->SetFloat3("light_pos", light_pos);
            shader->SetFloat3("view_pos", m_Camera->getPos());

            model = MAT4(1.0f);
            shader->SetMat4("model_matrix", model);
            shader->SetBool("isObj", true);
            VAO1->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            model = MAT4(1.0f);
            model = glm::translate(model, light_pos);
            model = glm::scale(model, VEC3(0.25, 0.25, 0.25));
            shader->SetMat4("model_matrix", model);
            shader->SetBool("isObj", false);
            VAO1->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // window/input-manager clearing functions
            m_InputManager->Update();
            m_Window->ClearEventQueue();
            m_Window->SwapBuffers();
            m_Window->PollEvents();

            auto frameEnd = std::chrono::steady_clock::now();
            auto timeDiff = frameEnd - frameStart;
            dt = std::chrono::duration<float>(timeDiff).count();

            auto current_time = std::chrono::steady_clock::now();

            if ((std::chrono::duration<float>(current_time - fps_count_time).count()) >= 1)
            {
                fps_count_time = current_time;
                int fps = 1/dt;
                STRING title = "FPS: ";
                title += std::to_string(fps);

                m_Window->EditWindowTitle(title);
            }
        }
    }
} // namespace Frisk
