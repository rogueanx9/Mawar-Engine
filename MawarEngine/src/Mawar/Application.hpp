#pragma once

#include "Mawar/Core.hpp"
#include "Mawar/Events/Event.hpp"
#include "Mawar/Events/ApplicationEvent.hpp"
#include "Mawar/Window.hpp"
#include "Mawar/LayerStack.hpp"
#include "Mawar/ImGui/ImGuiLayer.hpp"
#include "Mawar/Renderer/Shader.hpp"
#include "Mawar/Renderer/VertexArray.hpp"
#include "Mawar/Renderer/OrthographicCamera.hpp"

namespace Mawar
{
	class M_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay (Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool OnWindowClosed(WindowCloseEvent&);
		bool m_Running = true;
		float m_LastFrameTime;

	private:
		static Application* s_Instance;
	};

	// To be defined on client
	Application* CreateApplication();
}

