#include <MawarEngine.hpp>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

class LayerExample : public Mawar::Layer
{
public:
	LayerExample()
		: Layer("Example"), m_Camera(-2.0f, 2.0f, -1.5f, 1.5f), m_CameraPosition(0.0f), m_TransformPosition(0.0f)
	{
		/// <summary>
		/// OpenGL Rendering Object
		/// </summary>
		m_VertexArray.reset(Mawar::VertexArray::Create());
		m_SquareVertexArray.reset(Mawar::VertexArray::Create());

		/// <summary>
		/// Triangle
		/// </summary>
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		std::shared_ptr<Mawar::VertexBuffer> triangleVB;
		triangleVB.reset(Mawar::VertexBuffer::Create(vertices, sizeof(vertices)));
		triangleVB->SetLayout({
			{Mawar::ShaderDataType::Float3, "a_Position"},
			{Mawar::ShaderDataType::Float4, "a_Color"}
			});
		m_VertexArray->AddVertexBuffer(triangleVB);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<Mawar::IndexBuffer> triangleIB;
		triangleIB.reset(Mawar::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(triangleIB);

		/// <summary>
		/// Square
		/// </summary>
		float squareVertices[4 * 7] =
		{
			-0.75f, -0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
		};
		std::shared_ptr<Mawar::VertexBuffer> squareVB;
		squareVB.reset(Mawar::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Mawar::ShaderDataType::Float3, "a_Position"},
			{Mawar::ShaderDataType::Float4, "a_Color"}
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = { 0,1,2,2,3,0 };
		std::shared_ptr<Mawar::IndexBuffer> squareIB;
		squareIB.reset(Mawar::IndexBuffer::Create(squareIndices, 6));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
             #version 330 core

             layout(location=0) in vec3 a_Position;
             layout(location=1) in vec4 a_Color;

             uniform mat4 u_ViewProjection;
             uniform mat4 u_Transform;

             out vec3 v_Position;
             out vec4 v_Color;

             void main()
             {
                  v_Position = a_Position;
                  v_Color = a_Color;
                  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
             }
        )";

		std::string fragmentSource = R"(
             #version 330 core

             layout(location=0) out vec4 color;

             in vec3 v_Position;
             in vec4 v_Color;

             void main()
             {
                  color = vec4(v_Position * 0.5 + 0.6, 1.0);
                  color = v_Color;
             }
        )";

		m_Shader.reset(Mawar::Shader::Create(vertexSource, fragmentSource));

		std::string SquarevertexSource = R"(
             #version 330 core

             layout(location=0) in vec3 a_Position;
             layout(location=1) in vec4 a_Color;

             uniform mat4 u_ViewProjection;
             uniform mat4 u_Transform;

             out vec3 v_Position;
             out vec4 v_Color;

             void main()
             {
                  v_Position = a_Position;
                  v_Color = a_Color;
                  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
             }
        )";

		std::string SquarefragmentSource = R"(
             #version 330 core

             layout(location=0) out vec4 color;

             in vec3 v_Position;
             in vec4 v_Color;

             uniform vec4 u_Color;

             void main()
             {
                  color = u_Color;
             }
        )";

		m_SquareShader.reset(Mawar::Shader::Create(SquarevertexSource, SquarefragmentSource));
	}

	void OnUpdate(Mawar::Timestep ts) override
	{
		//M_TRACE("Delta time: {0}s {1}ms", ts.GetSecond(), ts.GetMiliSecond());

		if (Mawar::Input::IsKeyPressed(M_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
			
		if (Mawar::Input::IsKeyPressed(M_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
			
		if (Mawar::Input::IsKeyPressed(M_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_COMMA))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (Mawar::Input::IsKeyPressed(M_KEY_APOSTROPHE))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

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

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		Mawar::Renderer::BeginScene(m_Camera);

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

		glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), m_TransformPosition);
		Mawar::Renderer::Submit(m_Shader, m_VertexArray, transform1);
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
	}

private:
	ImVec4 TextCol = ImVec4{ 0.8f,0.8f,0.8f,1.0f };
	ImVec4 ClearColor = ImVec4{ 0.2f,0.2f,0.2f,1.0f };
	ImVec4 SquareColor = ImVec4{ 0.2f,0.3f,0.8f,1.0f };

	std::shared_ptr<Mawar::Shader> m_Shader;
	std::shared_ptr<Mawar::Shader> m_SquareShader;
	std::shared_ptr<Mawar::VertexArray> m_VertexArray;
	std::shared_ptr<Mawar::VertexArray> m_SquareVertexArray;

	Mawar::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.8f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;

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