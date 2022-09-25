#pragma once

#include <MawarEngine.hpp>
#include "imgui.h"

class LayerExample : public Mawar::Layer
{
public:
	LayerExample();

	void OnUpdate(Mawar::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Mawar::Event& e) override;

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