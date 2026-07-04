#include "Engine/Renderer/Renderer.h"
#include "OpenGL/OpenGLrendererB.h"
#include "OpenGL/OpenGLrendererI.h"

namespace Frisk {
	std::unique_ptr<Renderer> Renderer::CreateB() {
		// OpenGL for now
		return std::make_unique<OpenGLrendererB>();
	}

	std::unique_ptr<Renderer> Renderer::CreateI() {
		// OpenGL for now
		return std::make_unique<OpenGLrendererI>();
	}
}
