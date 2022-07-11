#pragma once

#ifdef M_PLATFORM_W10
	#ifdef M_BUILD_DLL
		#define M_API __declspec(dllexport)
	#else
		#define M_API __declspec(dllimport)
	#endif
#else
	#error Windows only!
#endif

#define BIT(x) (1 << x)

#ifdef M_ENABLE_ASSERT
	#define M_ASSERT(x, ...) if(!(x)) { M_ERROR("Assertion Error: {0}", __VA_ARGS__); __debugbreak();}
	#define M_CORE_ASSERT(x, ...) if(!(x)) { M_CORE_ERROR("Assertion Error: {0}", __VA_ARGS__); __debugbreak();}
#else
	#define M_ASSERT(x, ...)
	#define M_CORE_ASSERT(x, ...)
#endif