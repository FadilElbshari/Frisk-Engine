#pragma once

#include "Engine/Core/Types.h"
#include "GraphicsContext.h"

namespace Frisk {
	namespace Graphics {

		struct KeyEvent {
			int key;
			int action;
			int scancode;
			int mods;
		};

		struct MouseButtonEvent {
			int button;
			int action;
			int mods;
		};

		struct MouseMoveEvent {
			double x;
			double y;
		};

		using Event = std::variant<KeyEvent, MouseButtonEvent, MouseMoveEvent>;

		class Window {
		public:
			Window(U32 a_Width, U32 a_Height, STRING a_Title);
			~Window();

			bool Init();

			void SwapBuffers() const;
			void PollEvents() const;
			bool ShouldClose() const;

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
