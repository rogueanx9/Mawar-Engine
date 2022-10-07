#pragma once

#include "Mawar/Renderer/RendererAPI.hpp"

namespace Mawar
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		
		inline static void OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->OnWindowResize(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}