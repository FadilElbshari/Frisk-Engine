#pragma once

#include "Engine/Core/EngineAPI.h"
#include "Engine/Core/Types.h"

#include <memory>

namespace Frisk::Graphics
{
    class Window;
}

namespace Frisk
{
    class Camera;
}

namespace Frisk::Input
{
    class InputManager;
}

namespace Frisk
{

    struct ApplicationProps
    {
        U32 width = 0;
        U32 height = 0;
        STRING title;
        VEC3 background = VEC3(0, 0, 0);
    };

    class ENGINE_API Application
    {
      public:
        Application(const ApplicationProps &a_BuildProps);
        virtual ~Application();

        void Run();

      protected:
        virtual void OnUpdate() {} // this runs inside Run()

      private:
        std::unique_ptr<Graphics::Window> m_Window;
        std::unique_ptr<Input::InputManager> m_InputManager;
        std::unique_ptr<Camera> m_Camera;

        ApplicationProps m_Props;
    };
} // namespace Frisk
