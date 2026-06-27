#pragma once

#include "Engine/Core/Types.h"
#include "Window/GraphicsContext.h"
#include "Window/Event.h"

namespace Frisk {
	namespace Graphics {

		class Window {
		public:
			Window(U32 a_Width, U32 a_Height, STRING a_Title);
			~Window();

			bool Init();

			// run utility functions
			void SwapBuffers() const;
			void PollEvents() const;
			bool ShouldClose() const;

			// helper function wrappers
			void SetWindowBackGround(float r, float g, float b) const;
			void ClearColorBufferBit() const;

			const std::vector<Event>& GetEventQueue() const;
			void ClearEventQueue();

		private:

    		GLFWwindow* m_WindowHandle = nullptr;

    		std::unique_ptr<GraphicsContext> m_Context;
    		std::vector<Event> m_EventQueue;

    		U32 m_Width = 0;
    		U32 m_Height = 0;
    		STRING m_Title;

    		bool m_Running = false;

		};
	}
}
