#include "mpch.hpp"
#include "Renderer2D.hpp"

#include "Mawar/Renderer/VertexArray.hpp"
#include "Mawar/Renderer/Shader.hpp"
#include "Mawar/Renderer/RenderCommand.hpp"
#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

namespace Mawar
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> flatColorShader;
	};
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->quadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		auto squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		s_Data->quadVertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0,1,2,2,3,0 };
		s_Data->quadVertexArray->SetIndexBuffer(IndexBuffer::Create(squareIndices, 6));

		s_Data->flatColorShader = Shader::Create("assets/shaders/Square.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->flatColorShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4f("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->flatColorShader)->UploadUniformFloat4("u_Color", color);

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}
}