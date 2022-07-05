#include "Application.hpp"
#include <stdio.h>

namespace Mawar
{
	Application::Application() {}
	Application::~Application() {}

	void Application::Run()
	{
		printf("Mawar Engine is running...\n");
		while (true);
	}
}