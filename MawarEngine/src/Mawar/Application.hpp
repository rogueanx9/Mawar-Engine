#pragma once

#include "Mawar/Core.hpp"
#include "Mawar/Events/Event.hpp"
#include "Mawar/Events/ApplicationEvent.hpp"
#include "Mawar/Window.hpp"
#include "Mawar/LayerStack.hpp"

namespace Mawar
{
	class M_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay (Layer* layer);

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool OnWindowClosed(WindowCloseEvent&);
		bool m_Running = true;
	};

	// To be defined on client
	Application* CreateApplication();
}

