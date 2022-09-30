#pragma once

#include <MawarEngine.hpp>
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class Sandbox2D : public Mawar::Layer
{
public:
	Sandbox2D();
	~Sandbox2D();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Mawar::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Mawar::Event& e) override;

private:
	Mawar::QuadProps tileSquare;
	glm::vec4 m_ClearColor{ 0.2f,0.2f,0.2f,1.0f };
	glm::vec4 m_Color{ 0.2f,0.3f,0.8f,1.0f };
	glm::vec4 m_CatColor{ 0.6f,0.3f,0.8f,1.0f };
	Mawar::Ref<Mawar::Texture2D> m_Texture, m_CatTexture;

	Mawar::OrthographicCameraController m_CameraController;
	Mawar::Ref<Mawar::VertexArray> m_SquareVertexArray;

	/*struct ProfileResult
	{
		const char* name;
		float duration;
	};*/
	//std::vector<ProfileResult> m_ProfileResults;
};