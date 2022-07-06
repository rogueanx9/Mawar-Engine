#pragma once

#ifdef M_PLATFORM_W10

extern Mawar::Application* Mawar::CreateApplication();

int main()
{
	Mawar::Log::Init();
	M_CORE_WARN("Initialized Log!");
	int x = 5;
	M_INFO("int x = {0};", x);

	Mawar::Application* app = Mawar::CreateApplication();
	app->Run();
	delete app;
}

#endif