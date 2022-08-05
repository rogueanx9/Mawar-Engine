#include "mpch.hpp"
#include "VertexArray.hpp"

#include "Mawar/Log.hpp"
#include "Mawar/Renderer/Renderer.hpp"
#include "Mawar/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Mawar
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

}