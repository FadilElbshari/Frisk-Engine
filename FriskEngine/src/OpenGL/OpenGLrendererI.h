#include "Engine/Renderer/Renderer.h"
#include "Window/Buffer.h"
#include "Window/VertexArray.h"

#define MAX_QUADS_INSTANCED 1280 * 720

namespace Frisk
{

    struct InstancedData
    {
        VEC3 translation;
        VEC3 size;
        VEC3 color;
    };

    class OpenGLrendererI : public Renderer
    {
      public:
        OpenGLrendererI() = default;

        virtual ~OpenGLrendererI();

        virtual void Init() override;

        virtual void Beginframe() override;
        virtual void Assembleframe() override;
        virtual void Endframe() override;

        virtual void Submitquad(const VEC3 &a_Position, const VEC3 &a_Size, const VEC3 &a_Color) override;

        virtual void Shutdown() override;

      private:
        struct RendererData
        {
            std::unique_ptr<VertexArray> VAO;

            std::unique_ptr<VertexBuffer> VBObase;
            std::unique_ptr<VertexBuffer> VBOinstanced;

            std::shared_ptr<IndexBuffer> IBO;

            InstancedData *StartOfData = nullptr;
            InstancedData *Data = nullptr;

            U32 InstanceCount = 0;
        };

        RendererData m_Data;
    };
} // namespace Frisk
