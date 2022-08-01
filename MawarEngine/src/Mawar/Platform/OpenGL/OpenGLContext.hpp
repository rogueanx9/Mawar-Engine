#pragma once

#include "Mawar/Renderer/GraphicContext.hpp"

struct GLFWwindow;

namespace Mawar
{
	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}