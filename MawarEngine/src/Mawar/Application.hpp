#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

namespace Mawar
{
	class M_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined on client
	Application* CreateApplication();
}

