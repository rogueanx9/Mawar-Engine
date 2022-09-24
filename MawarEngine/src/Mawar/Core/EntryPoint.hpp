#pragma once

#ifdef M_PLATFORM_W10

extern Mawar::Application* Mawar::CreateApplication();

int main()
{
	Mawar::Log::Init();

	M_PROFILE_BEGIN_SESSION("Startup", "Mawar-Startup-Profiling.json");
	Mawar::Application* app = Mawar::CreateApplication();
	M_PROFILE_END_SESSION();

	M_PROFILE_BEGIN_SESSION("Runtime", "Mawar-Runtime-Profiling.json");
	app->Run();
	M_PROFILE_END_SESSION();

	M_PROFILE_BEGIN_SESSION("Shutdown", "Mawar-Shutdown-Profiling.json");
	delete app;
	M_PROFILE_END_SESSION();
}

#endif