#pragma once

namespace Frisk {
    class Renderer {
    public:

        virtual ~Renderer() = 0;
        virtual void Init() = 0;

        virtual void Beginframe() = 0;
        virtual void Assembleframe() = 0;
        virtual void Endframe() = 0;

        virtual void Submit() = 0;

        virtual void Shutdown() = 0;

    };
}
