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