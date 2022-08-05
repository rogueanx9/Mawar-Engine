#include "mpch.hpp"
#include "RenderCommand.hpp"

#include "Mawar/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Mawar
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}