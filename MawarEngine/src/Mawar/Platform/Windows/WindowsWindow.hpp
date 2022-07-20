#pragma once

#include "Mawar/Window.hpp"
#include <GLFW/glfw3.h>

namespace Mawar
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		void OnUpdate() override;

		// Window Attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.Callback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window = nullptr;

		struct WindowData
		{
			std::string Title;
			unsigned int Width = 0.0f;
			unsigned int Height = 0.0f;
			bool Vsync;
			EventCallbackFn Callback;
		};
		WindowData m_Data;
	};
}