#include <MawarEngine.hpp>

class LayerExample : public Mawar::Layer
{
public:
	LayerExample()
		: Layer("Example") {}

	void OnUpdate() override
	{
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