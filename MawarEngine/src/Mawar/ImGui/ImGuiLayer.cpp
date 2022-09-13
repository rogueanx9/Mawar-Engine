#include "mpch.hpp"
#include "ImGuiLayer.hpp"

#include "Mawar/Application.hpp"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

namespace Mawar
{
	static ImVec4 m_clear_color = { 0.2f, 0.2f, 0.2f, 1.0f };

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (m_show_demo_window)
			ImGui::ShowDemoWindow(&m_show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &m_show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &m_show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&m_clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (m_show_another_window)
		{
			ImGui::Begin("Another Window", &m_show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				m_show_another_window = false;
			ImGui::End();
		}
	}

	void ImGuiLayer::Begin()
	{
		// Initial setup for each frame
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		float time = (float)glfwGetTime();

		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/*
		 * int display_w, display_h;
		 * glfwGetFramebufferSize(window, &display_w, &display_h);
		 * glViewport(0, 0, display_w, display_h);
		 */

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			//GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}
	}
}