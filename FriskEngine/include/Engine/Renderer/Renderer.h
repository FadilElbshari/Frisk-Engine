#pragma once

#include "Engine/Core/Types.h"
#include <memory>

namespace Frisk
{
    class ENGINE_API Renderer
    {
      public:
        virtual ~Renderer() = default;
        virtual void Init() = 0;

        virtual void Beginframe() = 0;
        virtual void Assembleframe() = 0;
        virtual void Endframe() = 0;

        virtual void Submitquad(const VEC3 &a_Position, const VEC3 &a_Size, const VEC3 &a_Color) = 0;

        virtual void Shutdown() = 0;

        static std::unique_ptr<Renderer> CreateB();
        static std::unique_ptr<Renderer> CreateI();
    };
} // namespace Frisk
