#pragma once

#include "Mawar/Renderer/RenderCommand.hpp"
#include "Mawar/Renderer/OrthographicCamera.hpp"
#include "Mawar/Renderer/Shader.hpp"

namespace Mawar
{
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static ShaderLibrary* GetShaderLibrary() { return s_ShaderLibrary; }
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
		static ShaderLibrary* s_ShaderLibrary;
	};
}