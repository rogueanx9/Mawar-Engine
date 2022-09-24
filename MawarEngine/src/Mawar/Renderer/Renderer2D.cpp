#include "mpch.hpp"
#include "Renderer2D.hpp"

#include "Mawar/Renderer/VertexArray.hpp"
#include "Mawar/Renderer/Shader.hpp"
#include "Mawar/Renderer/RenderCommand.hpp"

namespace Mawar
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> textureShader = Shader::Create("assets/shaders/Texture.glsl");

		uint32_t white_data = 0xffffffff;
		Ref<Texture2D> whiteTexture = Texture2D::Create(1, 1, &white_data);
	};
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->quadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		auto squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		s_Data->quadVertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0,1,2,2,3,0 };
		s_Data->quadVertexArray->SetIndexBuffer(IndexBuffer::Create(squareIndices, 6));

		s_Data->textureShader->Bind();
		s_Data->textureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->textureShader->Bind();
		s_Data->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
		                      const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		s_Data->textureShader->SetFloat4("u_Color", color);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->textureShader->SetMat4("u_Transform", transform);

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
		const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, color, s_Data->whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, color, s_Data->whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(position, size, glm::vec4(1.0f), texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(position, size, glm::vec4(1.0f), texture);
	}
}