#pragma once

#include "Mawar/Renderer/RenderCommand.hpp"
#include "Mawar/Renderer/OrthographicCamera.hpp"
#include "Mawar/Renderer/Shader.hpp"

namespace Mawar
{
	class Renderer
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::unique_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}