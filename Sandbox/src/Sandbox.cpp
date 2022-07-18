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