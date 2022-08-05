#pragma once

#include "Mawar/Renderer/RenderCommand.hpp"

namespace Mawar
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}