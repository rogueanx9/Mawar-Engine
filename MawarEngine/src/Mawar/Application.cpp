#include "mpch.hpp"
#include "Application.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Log.hpp"

#include <GLFW/glfw3.h>

namespace Mawar
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Running = !(glfwWindowShouldClose(m_Window->GetGLFWWindow()));
			glClearColor(0.2, 0.5, 0.8, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}