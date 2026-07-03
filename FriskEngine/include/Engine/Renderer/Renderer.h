#pragma once

#include <memory>
#include "Engine/Core/Types.h"

namespace Frisk {
    class Renderer {
    public:

        virtual ~Renderer() = 0;
        virtual void Init() = 0;

        virtual void Beginframe() = 0;
        virtual void Assembleframe() = 0;
        virtual void Endframe() = 0;

        virtual void Submitquad(const VEC3& a_Position, const VEC3& a_Color) = 0;

        virtual void Shutdown() = 0;

        static std::unique_ptr<Renderer> Create();

    };
}
