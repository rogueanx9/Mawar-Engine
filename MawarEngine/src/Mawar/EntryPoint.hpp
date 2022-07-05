#pragma once

#include "Application.hpp"

#ifdef M_PLATFORM_W10

extern Mawar::Application* Mawar::CreateApplication();

int main()
{
	Mawar::Application* app = Mawar::CreateApplication();
	app->Run();
	delete app;
}

#endif