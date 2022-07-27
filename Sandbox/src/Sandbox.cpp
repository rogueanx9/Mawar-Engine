#include <MawarEngine.hpp>

#include "imgui.h"

class LayerExample : public Mawar::Layer
{
public:
	LayerExample()
		: Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnImGuiRender() override
	{
		{
			ImGui::Begin("Hello World!");
			ImGui::TextColored(TextCol, "Halo ini window baru dari layer example\npada aplikasi sandbox.");
			ImGui::ColorEdit3("clear color", (float*)&TextCol);
			ImGui::End();
		}
	}

	void OnEvent(Mawar::Event& e) override
	{
		if (e.GetEventType() == Mawar::EventType::KeyPressed)
		{
			Mawar::KeyPressedEvent& event = (Mawar::KeyPressedEvent&)e;
			M_TRACE("{0} is pressed.", (char)event.GetKeyCode());
		}
		else
			M_TRACE("{0}", e);
	}

private:
	ImVec4 TextCol = ImVec4{0.0f,0.0f,0.0f,1.0f};
};

class Sandbox : public Mawar::Application
{
public:
	Sandbox()
	{
		PushLayer(new LayerExample());
	}
	~Sandbox(){}
};

Mawar::Application* Mawar::CreateApplication()
{
	return new Sandbox();
}