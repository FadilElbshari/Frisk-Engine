#include "Engine/Renderer/Renderer.h"
#include "OpenGL/OpenGLrenderer.h"

namespace Frisk {
	std::unique_ptr<Renderer> Renderer::Create() {
		// OpenGL for now
		return std::make_unique<OpenGLrenderer>();
	}
}