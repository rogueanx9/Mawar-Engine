#pragma once

#include "Core.hpp"
#include "Mawar/Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Mawar/Window.hpp"

namespace Mawar
{
	class M_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

	private:
		bool OnWindowClosed(WindowCloseEvent&);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined on client
	Application* CreateApplication();
}

