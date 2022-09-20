#include "Sandbox2D.hpp"

#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D"), m_CameraController(4 / 3)
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Mawar::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	auto squareVB = Mawar::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{Mawar::ShaderDataType::Float3, "a_Position"}
		});
	m_SquareVertexArray->AddVertexBuffer(squareVB);

	unsigned int squareIndices[] = { 0,1,2,2,3,0 };
	m_SquareVertexArray->SetIndexBuffer(Mawar::IndexBuffer::Create(squareIndices, 6));

	Mawar::Renderer::GetShaderLibrary()->Add("FlatShader", Mawar::Shader::Create("assets/shaders/Square.glsl"));

	m_CameraController.SetRotation(true);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Mawar::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Mawar::RenderCommand::SetClearColor(m_ClearColor);
	Mawar::RenderCommand::Clear();

	Mawar::Renderer::BeginScene(m_CameraController.GetCamera());

	auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Get("FlatShader");

	std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);

	Mawar::Renderer::Submit(m_Shader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Mawar::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Sandbox 2D");
	ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mawar::Event& e)
{
	m_CameraController.OnEvent(e);
}
