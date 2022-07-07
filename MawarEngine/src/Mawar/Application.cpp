#include "Application.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Log.hpp"

namespace Mawar
{
	Application::Application() {}
	Application::~Application() {}

	void Application::Run()
	{
		WindowResizeEvent e{ 1280,720 };
		M_TRACE(e);

		KeyPressedEvent e1{ 10, 1 };
		M_TRACE(e1);

		MouseMovedEvent e2{ 100,50 };
		M_TRACE(e2);

		while (true);
	}
}