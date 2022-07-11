#include "mpch.hpp"
#include "WindowsWindow.hpp"

namespace Mawar
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.Vsync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		M_CORE_INFO("Creating Window {0} {1}x{2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			M_CORE_ASSERT(success, "Couldn't initialize GLFW.");
			s_GLFWInitialized = true;
		}
		M_CORE_TRACE("GLFW Initialized");

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		M_CORE_TRACE("Window Created");
		M_CORE_ASSERT(m_Window, "Couldn't create window.");

		glfwMakeContextCurrent(m_Window);
		M_CORE_TRACE("Make Context");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		M_CORE_TRACE("Set Window User Pointer");
		SetVSync(true);
		M_CORE_TRACE("Set VSync to true");
	}

	void WindowsWindow::Shutdown()
	{
		glfwTerminate();
	}
}
