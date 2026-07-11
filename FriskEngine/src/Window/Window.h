#pragma once

#include "Engine/Core/Types.h"
#include "Window/Event.h"
#include "Window/GraphicsContext.h"

namespace Frisk
{
    namespace Graphics
    {

        class Window
        {
          public:
            Window(U32 a_Width, U32 a_Height, STRING a_Title);
            ~Window();

            bool Init();

            // run utility functions
            void SwapBuffers() const;
            void PollEvents() const;
            bool ShouldClose() const;

            const VEC2& GetMousePos() const { return m_MousePos; }

            // helper function wrappers
            void SetWindowBackGround(float r, float g, float b) const;
            void ClearColorBufferBit() const;
            void Enable3D() const;
            void HideCursor() const;
            void ShowCursor() const;
            void EnableVSync() const;
            void DisableVSync() const;
            void EditWindowTitle(const STRING& a_Title);

            const std::vector<Event> &GetEventQueue() const;
            void ClearEventQueue();

          private:
            GLFWwindow *m_WindowHandle = nullptr;

            std::unique_ptr<GraphicsContext> m_Context;
            std::vector<Event> m_EventQueue;

            U32 m_Width = 0;
            U32 m_Height = 0;
            STRING m_Title;

            VEC2 m_MousePos = {0.0f, 0.0f};

            bool m_Running = false;
        };
    } // namespace Graphics
} // namespace Frisk
