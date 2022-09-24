#include "mpch.hpp"
#include "Application.hpp"

#include "Mawar/Renderer/Renderer.hpp"

#include "Mawar/Core/KeyCodes.hpp"
#include "Mawar/Core/Timestep.hpp"

#include<GLFW/glfw3.h>

namespace Mawar
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		M_PROFILE_FUNCTION();
		/// <summary>
		/// Initialization
		/// </summary>
		M_CORE_ASSERT(!s_Instance, "Application already running.");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		M_PROFILE_FUNCTION();
	}

	void Application::OnEvent(Event& e)
	{
		M_PROFILE_FUNCTION();

		EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		M_PROFILE_FUNCTION();

		while (m_Running)
		{
			M_PROFILE_SCOPE("RUN LOOP");
			float time = glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				M_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
				M_PROFILE_SCOPE("OnImGui Render");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			// Main Window Update
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		M_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		M_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		M_PROFILE_FUNCTION();

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		M_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		m_Minimized = false;
		return false;
	}
}