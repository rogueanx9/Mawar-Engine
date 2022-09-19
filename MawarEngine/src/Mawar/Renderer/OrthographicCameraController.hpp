#pragma once

#include "Mawar/Renderer/OrthographicCamera.hpp"
#include "Mawar/Core/Timestep.hpp"

#include "Mawar/Events/ApplicationEvent.hpp"
#include "Mawar/Events/MouseEvent.hpp"

namespace Mawar
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectratio, bool m_Rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		bool GetRotation() const { return m_Rotation; }
		void SetRotation(bool rotation) { m_Rotation = rotation; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio;
		bool m_Rotation;

		glm::vec3 m_CameraPosition{ 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 5.0f;

		OrthographicCamera m_Camera;
	};
}