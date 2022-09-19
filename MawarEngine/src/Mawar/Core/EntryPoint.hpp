#pragma once

#ifdef M_PLATFORM_W10

extern Mawar::Application* Mawar::CreateApplication();

int main()
{
	Mawar::Log::Init();
	M_CORE_INFO("Initialized Log!");

	Mawar::Application* app = Mawar::CreateApplication();
	app->Run();
	delete app;
}

#endif