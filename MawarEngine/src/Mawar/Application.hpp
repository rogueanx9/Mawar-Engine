#pragma once

#include "Core.hpp"
#include "Mawar/Events/Event.hpp"
#include "Mawar/Window.hpp"

namespace Mawar
{
	class M_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined on client
	Application* CreateApplication();
}

