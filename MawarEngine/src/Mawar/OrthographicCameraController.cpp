#include "mpch.hpp"
#include "OrthographicCameraController.hpp"

#include "Mawar/Input.hpp"
#include "Mawar/KeyCodes.hpp"

namespace Mawar
{
	OrthographicCameraController::OrthographicCameraController(float aspectratio, bool rotation)
		: m_Camera(-aspectratio * m_ZoomLevel, aspectratio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), 
		  m_AspectRatio(aspectratio),
		  m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(M_KEY_UP))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(M_KEY_DOWN))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(M_KEY_LEFT))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(M_KEY_RIGHT))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(M_KEY_COMMA))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(M_KEY_APOSTROPHE))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<MouseScrolledEvent>(M_BIND_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(M_BIND_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetOffsetY();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}

}
