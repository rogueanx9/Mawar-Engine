#include "Sandbox2D.hpp"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D"), m_CameraController(4 / 3)
{
	M_PROFILE_FUNCTION();
	m_CameraController.SetRotation(true);
}

Sandbox2D::~Sandbox2D()
{
	M_PROFILE_FUNCTION();
}

void Sandbox2D::OnAttach()
{
	M_PROFILE_FUNCTION();

	m_Texture = Mawar::Texture2D::Create("assets/images/bird.png");
	m_CatTexture = Mawar::Texture2D::Create("assets/images/cat.png");
	m_Spritesheet = Mawar::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 10.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::OnDetach()
{
	M_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Mawar::Timestep ts)
{
	M_PROFILE_FUNCTION();

	Mawar::Renderer2D::ResetStats();
	{
		M_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		M_PROFILE_SCOPE("Render Preparation");
		Mawar::RenderCommand::SetClearColor(m_ClearColor);
		Mawar::RenderCommand::Clear();
	}
#if 0
	{
		M_PROFILE_SCOPE("Render Draw");

		Mawar::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Mawar::Renderer2D::DrawQuad({ -0.3f, -0.5f }, { 0.5f,0.5f }, m_Color);
		Mawar::Renderer2D::DrawQuad({ -0.1f, -0.8f }, { 0.5f,0.5f }, glm::vec4{ 0.2f, 0.8f, 0.3f, 1.0f });
		Mawar::Renderer2D::DrawQuad({ 0.3f, 0.5f, -0.1f }, { 5.0f,5.0f }, m_Texture);
		Mawar::Renderer2D::DrawQuad({ 0.3f, 0.5f }, { 1.0f,1.0f }, m_CatColor, m_CatTexture);
		for (int i = 0; i < m_TileCol; i++)
			for (int j = 0;j < m_TileRow; j++)
		{
			tileSquare.position = { 1.5f + i / 2.0f, 1.5f + j / 2.0f, 0.2f};
			tileSquare.scale = { 0.3f, 0.3f };
			tileSquare.rotation = glm::radians((float)i * j);
			tileSquare.color = { (i % 4) * 0.25f, (j % 5) * 0.2f, 0.3f, 1.0f};
			Mawar::Renderer2D::DrawQuad(tileSquare);
		}
		Mawar::Renderer2D::DrawQuad(Mawar::Renderer2D::QuadProps());
		Mawar::Renderer2D::EndScene();
	}

	{
		M_PROFILE_SCOPE("Render Particle");

		if (Mawar::Input::IsMouseButtonPressed(M_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = Mawar::Input::GetMousePosition();
			auto width = Mawar::Application::Get().GetWindow().GetWidth();
			auto height = Mawar::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetCamera().GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			x = (x / width) * bounds.x - bounds.x * 0.5f;
			y = bounds.y * 0.5f - (y / height) * bounds.y;
			m_Particle.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 20; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);

		Mawar::Renderer2D::BeginScene(m_CameraController.GetCamera());
		m_ParticleSystem.OnRender();
		Mawar::Renderer2D::EndScene();
	}
#else
	{
		Mawar::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Mawar::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Spritesheet);
		Mawar::Renderer2D::EndScene();
	}
#endif
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Sandbox 2D");
	ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));
	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
	//ImGui::ColorEdit4("Cat Tint Color", glm::value_ptr(m_CatColor));
	ImGui::SliderInt("Tile Row", &m_TileRow, 1, 200);
	ImGui::SliderInt("Tile Column", &m_TileCol, 1, 200);
	ImGui::Text("Draw calls: %d", Mawar::Renderer2D::GetStatistics().DrawCall);
	ImGui::Text("Quad count: %d", Mawar::Renderer2D::GetStatistics().Quad);
	ImGui::Text("Vertice count: %d", Mawar::Renderer2D::GetStatistics().GetVertices());
	ImGui::Text("Indice count: %d", Mawar::Renderer2D::GetStatistics().GetIndices());
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2D::OnEvent(Mawar::Event& e)
{
	m_CameraController.OnEvent(e);
}
