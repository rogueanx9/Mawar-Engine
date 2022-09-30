#include "Sandbox2D.hpp"

#include <chrono>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D"), m_CameraController(4 / 3)
{
	M_PROFILE_FUNCTION();

	m_Texture = Mawar::Texture2D::Create("assets/images/bird.png");
	m_CatTexture = Mawar::Texture2D::Create("assets/images/cat.png");
}

Sandbox2D::~Sandbox2D()
{
	M_PROFILE_FUNCTION();
}

void Sandbox2D::OnAttach()
{
	M_PROFILE_FUNCTION();

	m_CameraController.SetRotation(true);
}

void Sandbox2D::OnDetach()
{
	M_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Mawar::Timestep ts)
{
	M_PROFILE_FUNCTION();

	{
		M_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		M_PROFILE_SCOPE("Render Preparation");
		Mawar::RenderCommand::SetClearColor(m_ClearColor);
		Mawar::RenderCommand::Clear();
	}

	{
		M_PROFILE_SCOPE("Render Draw");
		Mawar::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Mawar::Renderer2D::DrawQuad({ -0.3f, -0.5f }, { 0.5f,0.5f }, m_Color);
		Mawar::Renderer2D::DrawQuad({ -0.1f, -0.8f }, { 0.5f,0.5f }, glm::vec4{ 0.2f, 0.8f, 0.3f, 1.0f });
		Mawar::Renderer2D::DrawQuad({ 0.3f, 0.5f, -0.1f }, { 5.0f,5.0f }, m_Texture);
		Mawar::Renderer2D::DrawQuad({ 0.3f, 0.5f }, { 1.0f,1.0f }, m_CatColor, m_CatTexture);
		for (int i = 0; i < 5; i++)
			for (int j = 0;j<5;j++)
		{
			tileSquare.position = { 1.5f + i / 2.0f, 1.5f + j / 2.0f };
			tileSquare.scale = { 0.3f, 0.3f };
			tileSquare.rotation = glm::radians((float)i * j * 5);
			Mawar::Renderer2D::DrawQuad(tileSquare);
		}
		Mawar::Renderer2D::DrawQuad(Mawar::Renderer2D::QuadProps());
		Mawar::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Sandbox 2D");
	ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
	ImGui::ColorEdit4("Cat Tint Color", glm::value_ptr(m_CatColor));
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2D::OnEvent(Mawar::Event& e)
{
	m_CameraController.OnEvent(e);
}
