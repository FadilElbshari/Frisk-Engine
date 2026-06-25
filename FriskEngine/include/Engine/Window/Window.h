#pragma once

#include "Engine/Core/Types.h"
#include "Engine/Core/EngineAPI.h"

namespace Frisk {
	namespace Graphics {

		class ENGINE_API Window {
		public:
			Window(U32 a_Width, U32 a_Height, STRING a_Title);
			~Window() = default;

			bool Init();

			bool ShouldClose() const;

		private:
			struct Impl;
			std::unique_ptr<Impl> m_Impl;

		};
	}
}

