#include "mpch.hpp"
#include "VertexArray.hpp"

#include "Mawar/Renderer/Renderer.hpp"
#include "Mawar/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Mawar
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

}