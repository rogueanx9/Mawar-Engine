#include "mpch.hpp"
#include "WindowsInput.hpp"
#include "Mawar/Core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Mawar
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressed_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressed_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosition_impl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseX_impl()
	{
		auto [x, y] = GetMousePosition_impl();
		return x;
	}

	float WindowsInput::GetMouseY_impl()
	{
		auto [x, y] = GetMousePosition_impl();
		return y;
	}

}