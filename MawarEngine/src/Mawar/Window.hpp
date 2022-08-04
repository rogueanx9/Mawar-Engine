#pragma once

#include "Mawar/Core.hpp"
#include "Mawar/Events/Event.hpp"
#include "Mawar/Log.hpp"

namespace Mawar
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string title = "Mawar Engine",
			        unsigned int width = 800,
			        unsigned int height = 600)
			: Title(title), Width(width), Height(height) {}
	};

	class M_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}