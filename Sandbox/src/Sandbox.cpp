#include <MawarEngine.hpp>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

class LayerExample : public Mawar::Layer
{
public:
	LayerExample()
		: Layer("Example"), m_CameraController(4/3), m_TransformPosition(0.0f)
	{
		/// <summary>
		/// OpenGL Rendering Object
		/// </summary>
		m_VertexArray.reset(Mawar::VertexArray::Create());
		m_SquareVertexArray.reset(Mawar::VertexArray::Create());

		/// <summary>
		/// Triangle
		/// </summary>
		float vertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Mawar::Ref<Mawar::VertexBuffer> triangleVB;
		triangleVB.reset(Mawar::VertexBuffer::Create(vertices, sizeof(vertices)));
		triangleVB->SetLayout({
			{Mawar::ShaderDataType::Float3, "a_Position"},
			{Mawar::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_VertexArray->AddVertexBuffer(triangleVB);

		unsigned int indices[6] = { 0,1,2,2,3,0 };
		Mawar::Ref<Mawar::IndexBuffer> triangleIB;
		triangleIB.reset(Mawar::IndexBuffer::Create(indices, 6));
		m_VertexArray->SetIndexBuffer(triangleIB);

		/// <summary>
		/// Square
		/// </summary>
		float squareVertices[5 * 4] =
		{
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};
		Mawar::Ref<Mawar::VertexBuffer> squareVB;
		squareVB.reset(Mawar::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Mawar::ShaderDataType::Float3, "a_Position"},
			{Mawar::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0,1,2,2,3,0 };
		Mawar::Ref<Mawar::IndexBuffer> squareIB;
		squareIB.reset(Mawar::IndexBuffer::Create(squareIndices, 6));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Load("assets/shaders/Texture.glsl");

		std::string SquarevertexSource = R"(
             #version 330 core

             layout(location=0) in vec3 a_Position;
             layout(location=1) in vec2 a_TexCoord;

             uniform mat4 u_ViewProjection;
             uniform mat4 u_Transform;

             out vec3 v_Position;
             out vec2 v_TexCoord;

             void main()
             {
                  v_Position = a_Position;
                  v_TexCoord = a_TexCoord;
                  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
             }
        )";

		std::string SquarefragmentSource = R"(
             #version 330 core

             layout(location=0) out vec4 color;

             in vec3 v_Position;
             in vec2 v_TexCoord;

             uniform vec4 u_Color;

             void main()
             {
                  color = u_Color;
             }
        )";

		Mawar::Renderer::GetShaderLibrary()->Add(Mawar::Shader::Create("SquareShader", SquarevertexSource, SquarefragmentSource));

		m_Texture = Mawar::Texture2D::Create("assets/images/bird.png");
		m_CatTexture = Mawar::Texture2D::Create("assets/images/cat.png");
		std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0); // Upload slot ID
	}

	void OnUpdate(Mawar::Timestep ts) override
	{
		//M_TRACE("Delta time: {0}s {1}ms", ts.GetSecond(), ts.GetMiliSecond());
		m_CameraController.OnUpdate(ts);

		if (Mawar::Input::IsKeyPressed(M_KEY_W))
			m_TransformPosition.y += m_TransformMoveSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_S))
			m_TransformPosition.y -= m_TransformMoveSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_A))
			m_TransformPosition.x -= m_TransformMoveSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_D))
			m_TransformPosition.x += m_TransformMoveSpeed * ts;

		Mawar::RenderCommand::SetClearColor({ ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w });
		Mawar::RenderCommand::Clear();

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		Mawar::Renderer::BeginScene(m_CameraController.GetCamera());

		auto m_SquareShader = Mawar::Renderer::GetShaderLibrary()->Get("SquareShader");
		m_SquareShader->Bind();
		glm::vec4 square_color(SquareColor.x, SquareColor.y, SquareColor.z, SquareColor.w);
		std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_SquareShader)->UploadUniformFloat4("u_Color", square_color);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				glm::vec3 pos(0.18f * j, 0.18f * i, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Mawar::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
			}
		}

		auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Get("Texture");

		glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), m_TransformPosition);
		glm::mat4 moveSlight = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.0f));
		m_Texture->Bind();
		Mawar::Renderer::Submit(m_Shader, m_VertexArray, transform1);
		m_CatTexture->Bind();
		Mawar::Renderer::Submit(m_Shader, m_VertexArray, transform1 + moveSlight);
		Mawar::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		{
			ImGui::Begin("Hello World!");
			ImGui::TextColored(TextCol, "Halo ini window baru dari layer example\npada aplikasi sandbox.");
			ImGui::ColorEdit3("Text Color", (float*)&TextCol);
			ImGui::ColorEdit3("Clear Color", (float*)&ClearColor);
			ImGui::ColorEdit3("Square Color", (float*)&SquareColor);
			ImGui::End();
		}
	}

	void OnEvent(Mawar::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	ImVec4 TextCol = ImVec4{ 0.8f,0.8f,0.8f,1.0f };
	ImVec4 ClearColor = ImVec4{ 0.2f,0.2f,0.2f,1.0f };
	ImVec4 SquareColor = ImVec4{ 0.2f,0.3f,0.8f,1.0f };

	Mawar::Ref<Mawar::VertexArray> m_VertexArray;
	Mawar::Ref<Mawar::VertexArray> m_SquareVertexArray;

	Mawar::Ref<Mawar::Texture2D> m_Texture, m_CatTexture;

	Mawar::OrthographicCameraController m_CameraController;

	glm::vec3 m_TransformPosition;
	float m_TransformMoveSpeed = 1.0f;
};

class Sandbox : public Mawar::Application
{
public:
	Sandbox()
	{
		PushLayer(new LayerExample());
	}
	~Sandbox(){}
};

Mawar::Application* Mawar::CreateApplication()
{
	return new Sandbox();
}