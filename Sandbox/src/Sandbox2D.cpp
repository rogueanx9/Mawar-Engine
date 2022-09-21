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

	Mawar::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Mawar::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f,1.0f }, m_Color);

	Mawar::Renderer2D::EndScene();

	// auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Get("FlatShader"); // TODO: ShaderLib for Renderer2D
	//std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->Bind();
	//std::dynamic_pointer_cast<Mawar::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);
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
