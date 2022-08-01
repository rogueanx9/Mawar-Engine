#pragma once

#include "Mawar/Window.hpp"
#include "Mawar/Renderer/GraphicContext.hpp"

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

		void* GetNativeWindow() const override { return m_Window; }

	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window = nullptr;
		GraphicContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;
			bool Vsync;
			EventCallbackFn Callback;
		};
		WindowData m_Data;
	};
}