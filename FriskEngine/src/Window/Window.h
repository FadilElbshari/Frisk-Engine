#pragma once

#include "Engine/Core/Types.h"
#include "Engine/Core/EngineAPI.h"

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
			bool ShouldClose() const;

			const std::vector<Event>& GetEventQueue() const;
			void ClearEventQueue();

		private:
			struct Impl;
			std::unique_ptr<Impl> m_Impl;

		};
	}
}

