#include "mpch.hpp"
#include "OpenGLContext.hpp"
#include "Mawar/Log.hpp"

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
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}