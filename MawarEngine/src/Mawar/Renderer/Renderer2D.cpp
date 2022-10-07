#include "mpch.hpp"
#include "Renderer2D.hpp"

#include "Mawar/Renderer/VertexArray.hpp"
#include "Mawar/Renderer/Shader.hpp"
#include "Mawar/Renderer/RenderCommand.hpp"

namespace Mawar
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		// TODO: texID
	};

	struct Renderer2DStorage
	{
		const uint32_t MAX_QUADS = 10000;
		const uint32_t MAX_VERTICES = 4 * MAX_QUADS;
		const uint32_t MAX_INDICES  = 6 * MAX_QUADS;

		uint32_t quadIndexCount = 0;

		Ref<VertexBuffer> quadVertexBuffer;
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> textureShader;

		Ref<Texture2D> whiteTexture;

		QuadVertex* quadVertexBase = nullptr;
		QuadVertex* quadVertexPtr = nullptr;
	};
	static Renderer2DStorage s_Data;

	void Renderer2D::Init()
	{
		M_PROFILE_FUNCTION();

		s_Data.quadVertexArray = VertexArray::Create();

		s_Data.quadVertexBuffer = VertexBuffer::Create(s_Data.MAX_VERTICES * sizeof(QuadVertex));
		s_Data.quadVertexBase = new QuadVertex[s_Data.MAX_VERTICES];

		s_Data.quadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		s_Data.quadVertexArray->AddVertexBuffer(s_Data.quadVertexBuffer);

		uint32_t* quadIndices = new uint32_t[s_Data.MAX_INDICES];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MAX_INDICES; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		s_Data.quadVertexArray->SetIndexBuffer(IndexBuffer::Create(quadIndices, s_Data.MAX_INDICES));
		delete[] quadIndices;

		s_Data.textureShader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data.textureShader->Bind();
		uint32_t white_data = 0xffffffff;
		s_Data.whiteTexture = Texture2D::Create(1, 1, &white_data);

		//s_Data.textureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		M_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		M_PROFILE_FUNCTION();

		s_Data.textureShader->Bind();
		s_Data.textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.quadVertexPtr = s_Data.quadVertexBase;
	}

	void Renderer2D::EndScene()
	{
		M_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.quadVertexPtr - (uint8_t*)s_Data.quadVertexBase; // Bytes
		s_Data.quadVertexBuffer->SetData(s_Data.quadVertexBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		M_PROFILE_FUNCTION();

		RenderCommand::DrawIndexed(s_Data.quadVertexArray, s_Data.quadIndexCount);
	}

	void Renderer2D::DrawQuad(const QuadProps& quadProps)
	{
		M_PROFILE_FUNCTION();

		AddQuadVertex(quadProps);

		//s_Data.textureShader->SetFloat("u_TilingFactor", quadProps.tilingFactor);
		//s_Data.textureShader->SetFloat4("u_Color", { quadProps.color.r, quadProps.color.g, quadProps.color.b, quadProps.color.a });
		//quadProps.texture ? quadProps.texture->Bind() : s_Data.whiteTexture->Bind();

		/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), { quadProps.position.x, quadProps.position.y, quadProps.position.z });
		transform = quadProps.scale.x == 1.0f && quadProps.scale.y == 1.0f ?
			transform : 
			transform * glm::scale(glm::mat4(1.0f), { quadProps.scale.x, quadProps.scale.y, 1.0f });
		transform = quadProps.rotation == 0.0f ? 
			transform : 
			transform * glm::rotate(glm::mat4(1.0f), quadProps.rotation, { 0.0f, 0.0f, 1.0f });
		s_Data.textureShader->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
		                      const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		M_PROFILE_FUNCTION();

		QuadProps quadProps;
		quadProps.position.x = position.x;
		quadProps.position.y = position.y;
		quadProps.position.z = position.z;

		quadProps.scale.x = size.x;
		quadProps.scale.y = size.y;

		quadProps.color.r = color.x;
		quadProps.color.g = color.y;
		quadProps.color.b = color.z;
		quadProps.color.a = color.w;

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
		DrawQuad(position, size, color, s_Data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, color, s_Data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(position, size, glm::vec4(1.0f), texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(position, size, glm::vec4(1.0f), texture);
	}

	void Renderer2D::AddQuadVertex(const QuadProps& quadProps)
	{
		s_Data.quadVertexPtr->position = {
			quadProps.position.x,
			quadProps.position.y,
			quadProps.position.z
		};
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 0.0f, 0.0f };
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = {
			quadProps.position.x + quadProps.scale.x,
			quadProps.position.y,
			quadProps.position.z
		};
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 1.0f, 0.0f };
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = {
			quadProps.position.x + quadProps.scale.x,
			quadProps.position.y + quadProps.scale.y,
			quadProps.position.z
		};
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 1.0f, 1.0f };
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = {
			quadProps.position.x,
			quadProps.position.y + quadProps.scale.y,
			quadProps.position.z
		};
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 0.0f, 1.0f };
		s_Data.quadVertexPtr++;

		s_Data.quadIndexCount += 6;
	}
}