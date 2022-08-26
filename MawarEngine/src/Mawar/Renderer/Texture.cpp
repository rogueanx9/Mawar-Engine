#include "mpch.hpp"
#include "Texture.hpp"

#include "Mawar/Log.hpp"
#include "Mawar/Renderer/Renderer.hpp"
#include "Mawar/Platform/OpenGL/OpenGLTexture.hpp"

namespace Mawar
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}