#include <MawarEngine.hpp>
#include "Mawar/Core/EntryPoint.hpp"

#include "Sandbox2D.hpp"
#include "ExampleLayer.hpp"

class Sandbox : public Mawar::Application
{
public:
	Sandbox()
	{
		//PushLayer(new LayerExample());
		PushLayer(new Sandbox2D());
	}
	~Sandbox(){}
};

Mawar::Application* Mawar::CreateApplication()
{
	return new Sandbox();
}