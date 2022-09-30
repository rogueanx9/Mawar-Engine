#include "mpch.hpp"
#include "Renderer2D.hpp"

#include "Mawar/Renderer/VertexArray.hpp"
#include "Mawar/Renderer/Shader.hpp"
#include "Mawar/Renderer/RenderCommand.hpp"

namespace Mawar
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray = VertexArray::Create();
		Ref<Shader> textureShader = Shader::Create("assets/shaders/Texture.glsl");

		uint32_t white_data = 0xffffffff;
		Ref<Texture2D> whiteTexture = Texture2D::Create(1, 1, &white_data);
	};
	static Renderer2DStorage* s_Data = nullptr;

	void Renderer2D::Init()
	{
		M_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();

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
		M_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		M_PROFILE_FUNCTION();

		s_Data->textureShader->Bind();
		s_Data->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		M_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const QuadProps& quadProps)
	{
		M_PROFILE_FUNCTION();

		s_Data->textureShader->SetFloat("u_TilingFactor", quadProps.tilingFactor);
		s_Data->textureShader->SetFloat4("u_Color", { quadProps.r, quadProps.g, quadProps.b, quadProps.a });
		quadProps.texture ? quadProps.texture->Bind() : s_Data->whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { quadProps.x, quadProps.y, quadProps.z });
		transform = quadProps.scaleX == 1.0f && quadProps.scaleY == 1.0f ?
			transform : 
			transform * glm::scale(glm::mat4(1.0f), { quadProps.scaleX, quadProps.scaleY, 1.0f });
		transform = quadProps.rotation == 0.0f ? 
			transform : 
			transform * glm::rotate(glm::mat4(1.0f), quadProps.rotation, { 0.0f, 0.0f, 1.0f });
		s_Data->textureShader->SetMat4("u_Transform", transform);

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
		                      const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		M_PROFILE_FUNCTION();

		QuadProps quadProps;
		quadProps.x = position.x;
		quadProps.y = position.y;
		quadProps.z = position.z;

		quadProps.scaleX = size.x;
		quadProps.scaleY = size.y;

		quadProps.r = color.x;
		quadProps.g = color.y;
		quadProps.b = color.z;
		quadProps.a = color.w;

		quadProps.texture = texture;
		DrawQuad(quadProps);
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