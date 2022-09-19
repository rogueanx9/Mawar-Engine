#include "mpch.hpp"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Mawar
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
	{
		M_CORE_ASSERT(window, "Window Handle is null.")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		M_CORE_TRACE("Make Context");
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		M_CORE_TRACE("Initialized Glad");
		M_CORE_ASSERT(status, "Couldn't initialize Glad.");

		M_CORE_INFO("OpenGL Info:");
		M_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		M_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		M_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}