#pragma once

#include "Mawar/Renderer/OrthographicCamera.hpp"
#include "Mawar/Renderer/Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Mawar
{
	class Renderer2D
	{
	public:
		struct QuadProps
		{
			struct Position { float x = 0.0f, y = 0.0f, z = 0.0f; };
			struct Scale { float x = 1.0f, y = 1.0f; };
			struct Color { float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f; };

			Position position;
			Scale scale;
			Color color;
			float rotation = 0.0f; // radians
			float tilingFactor = 1.0f;
			Ref<Texture2D> texture;
		};

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const QuadProps& quadProps);

		// Legacy
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, 
			                 const glm::vec4& color, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
			                 const glm::vec4& color, const Ref<Texture2D>& texture);

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);

	private:
		static void AddQuadVertex(const QuadProps& quadProps);
	};
}