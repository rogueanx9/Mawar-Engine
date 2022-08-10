#include <MawarEngine.hpp>

#include "imgui.h"

class LayerExample : public Mawar::Layer
{
public:
	LayerExample()
		: Layer("Example"), m_Camera(-2.0f, 2.0f, -1.5f, 1.5f), m_CameraPosition(0.0f)
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

             out vec3 v_Position;
             out vec4 v_Color;

             void main()
             {
                  v_Position = a_Position;
                  v_Color = a_Color;
                  gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Mawar::Shader(vertexSource, fragmentSource));
	}

	void OnUpdate() override
	{
		if (Mawar::Input::IsKeyPressed(M_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Mawar::Input::IsKeyPressed(M_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
			
		if (Mawar::Input::IsKeyPressed(M_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
			
		if (Mawar::Input::IsKeyPressed(M_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Mawar::Input::IsKeyPressed(M_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;

		if (Mawar::Input::IsKeyPressed(M_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		glm::vec4 clear_color = { 0.2f,0.2f,0.2f,1.0f };

		Mawar::RenderCommand::SetClearColor({ clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w });
		Mawar::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Mawar::Renderer::BeginScene(m_Camera);
		Mawar::Renderer::Submit(m_Shader, m_SquareVertexArray);
		Mawar::Renderer::Submit(m_Shader, m_VertexArray);
		Mawar::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		{
			ImGui::Begin("Hello World!");
			ImGui::TextColored(TextCol, "Halo ini window baru dari layer example\npada aplikasi sandbox.");
			ImGui::ColorEdit3("clear color", (float*)&TextCol);
			ImGui::End();
		}
	}

	void OnEvent(Mawar::Event& e) override
	{
	}

private:
	ImVec4 TextCol = ImVec4{ 0.0f,0.0f,0.0f,1.0f };

	std::unique_ptr<Mawar::Shader> m_Shader;
	std::shared_ptr<Mawar::VertexArray> m_VertexArray;
	std::shared_ptr<Mawar::VertexArray> m_SquareVertexArray;

	Mawar::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
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