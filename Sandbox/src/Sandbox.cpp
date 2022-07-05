#include <MawarEngine.hpp>

class Sandbox : public Mawar::Application
{
public:
	Sandbox(){}
	~Sandbox(){}
};

Mawar::Application* Mawar::CreateApplication()
{
	return new Sandbox();
}