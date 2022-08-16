#include "mpch.hpp"
#include "Shader.hpp"

#include "Mawar/Renderer/Renderer.hpp"

#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

namespace Mawar
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}
