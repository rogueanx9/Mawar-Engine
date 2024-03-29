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
		float texId;
		float tilingFactor;
	};

	struct Renderer2DStorage
	{
		static const uint32_t MAX_QUADS = 20000;
		static const uint32_t MAX_VERTICES = 4 * MAX_QUADS;
		static const uint32_t MAX_INDICES  = 6 * MAX_QUADS;
		static const uint32_t MAX_TEX_SLOTS = 32; // TODO: Dynamic according to hardware

		uint32_t quadIndexCount = 0;

		Ref<VertexBuffer> quadVertexBuffer;
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> textureShader;

		Ref<Texture2D> whiteTexture;

		QuadVertex* quadVertexBase = nullptr;
		QuadVertex* quadVertexPtr = nullptr;

		std::array<Ref<Texture2D>, MAX_TEX_SLOTS> texSlots;
		uint32_t currentTexIndex = 1; // Reserve 0 for white texture

		glm::vec4 verticesPosition[4];

		Renderer2D::Statistics stats;
	};
	static Renderer2DStorage s_Data;

	void Renderer2D::Init()
	{
		M_PROFILE_FUNCTION();

		s_Data.quadVertexArray = VertexArray::Create();

		s_Data.quadVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MAX_VERTICES * sizeof(QuadVertex));
		s_Data.quadVertexBase = new QuadVertex[Renderer2DStorage::MAX_VERTICES];

		s_Data.quadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float, "a_TexId"},
			{ShaderDataType::Float, "a_TilingFactor"},
			});
		s_Data.quadVertexArray->AddVertexBuffer(s_Data.quadVertexBuffer);

		uint32_t* quadIndices = new uint32_t[Renderer2DStorage::MAX_INDICES];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < Renderer2DStorage::MAX_INDICES; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		s_Data.quadVertexArray->SetIndexBuffer(IndexBuffer::Create(quadIndices, Renderer2DStorage::MAX_INDICES));
		delete[] quadIndices;

		s_Data.textureShader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data.textureShader->Bind();
		uint32_t white_data = 0xffffffff;
		s_Data.whiteTexture = Texture2D::Create(1, 1, &white_data);

		int sampler2D[s_Data.MAX_TEX_SLOTS];
		for (uint32_t i = 0; i < s_Data.MAX_TEX_SLOTS; i++)
			sampler2D[i] = i;
		s_Data.textureShader->SetIntArray("u_Textures", s_Data.MAX_TEX_SLOTS, sampler2D);

		s_Data.verticesPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.verticesPosition[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.verticesPosition[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.verticesPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		M_PROFILE_FUNCTION();
	}

	void Renderer2D::ResetBatch()
	{
		s_Data.quadIndexCount = 0;
		s_Data.currentTexIndex = 1;
		s_Data.quadVertexPtr = s_Data.quadVertexBase;
		s_Data.texSlots[0] = s_Data.whiteTexture;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		M_PROFILE_FUNCTION();

		s_Data.textureShader->Bind();
		s_Data.textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		ResetBatch();
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

		// Bind textures
		for (uint32_t i = 0; i < s_Data.currentTexIndex; i++)
			s_Data.texSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.quadVertexArray, s_Data.quadIndexCount);

		s_Data.stats.DrawCall++;
	}

	void Renderer2D::DrawQuad(const QuadProps& quadProps)
	{
		M_PROFILE_FUNCTION();

		if (s_Data.quadIndexCount  >= Renderer2DStorage::MAX_INDICES || 
			s_Data.currentTexIndex >= Renderer2DStorage::MAX_TEX_SLOTS)
		{
			EndScene();
			ResetBatch();
		}

		// texture
		float textureID = -1.0f; // -1 because tex id is not a negative value
		Ref<Texture2D> texture = quadProps.texture ? quadProps.texture : s_Data.whiteTexture;

		for (uint32_t i = 0; i < s_Data.currentTexIndex; i++)
		{
			if (*s_Data.texSlots[i].get() == *texture.get())
				textureID = (float)i;
		}

		if (textureID == -1.0f)
		{
			textureID = (float)s_Data.currentTexIndex;
			s_Data.texSlots[s_Data.currentTexIndex] = quadProps.texture;
			s_Data.currentTexIndex++;
		}

		// transform
		glm::mat4 transform = Translate(quadProps) * Rotate(quadProps) * Scale(quadProps);

		s_Data.quadVertexPtr->position = transform * s_Data.verticesPosition[0];
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 0.0f, 0.0f };
		s_Data.quadVertexPtr->texId = textureID;
		s_Data.quadVertexPtr->tilingFactor = quadProps.tilingFactor;
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = transform * s_Data.verticesPosition[1];
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 1.0f, 0.0f };
		s_Data.quadVertexPtr->texId = textureID;
		s_Data.quadVertexPtr->tilingFactor = quadProps.tilingFactor;
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = transform * s_Data.verticesPosition[2];
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 1.0f, 1.0f };
		s_Data.quadVertexPtr->texId = textureID;
		s_Data.quadVertexPtr->tilingFactor = quadProps.tilingFactor;
		s_Data.quadVertexPtr++;

		s_Data.quadVertexPtr->position = transform * s_Data.verticesPosition[3];
		s_Data.quadVertexPtr->color = {
			quadProps.color.r,
			quadProps.color.g,
			quadProps.color.b,
			quadProps.color.a
		};
		s_Data.quadVertexPtr->texCoord = { 0.0f, 1.0f };
		s_Data.quadVertexPtr->texId = textureID;
		s_Data.quadVertexPtr->tilingFactor = quadProps.tilingFactor;
		s_Data.quadVertexPtr++;

		s_Data.quadIndexCount += 6;

		s_Data.stats.Quad++;
	}

	// Statistics
	Renderer2D::Statistics Renderer2D::GetStatistics()
	{
		return s_Data.stats;
	}

	void Renderer2D::ResetStats()
	{
		s_Data.stats.DrawCall = 0;
		s_Data.stats.Quad = 0;
	}

	// Legacy
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
}