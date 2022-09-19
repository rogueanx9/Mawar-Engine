#include "mpch.hpp"
#include "RenderCommand.hpp"

#include "Mawar/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Mawar
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}