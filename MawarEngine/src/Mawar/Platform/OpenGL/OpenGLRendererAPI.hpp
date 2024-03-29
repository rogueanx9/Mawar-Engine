#pragma once

#include "Mawar/Renderer/RendererAPI.hpp"

namespace Mawar
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
	};
}
