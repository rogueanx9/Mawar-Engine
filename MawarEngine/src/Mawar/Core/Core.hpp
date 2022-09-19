#pragma once

#include <memory>

// Platform detection using pre-defined macros
#ifdef _WIN32
	// Check if x64
	#ifdef _WIN64
		#define M_PLATFORM_W10
	#else
		#error Mawar only support 64 bit!
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define M_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define M_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple's platform!"
	#endif

/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define M_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define M_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection


#ifdef M_PLATFORM_W10
#ifdef M_DYNAMIC_LINK
	#ifdef M_BUILD_DLL
		#define M_API __declspec(dllexport)
	#else
		#define M_API __declspec(dllimport)
	#endif
#else
	#define M_API
#endif
#else
	#error Windows only!
#endif

#define BIT(x) (1 << x)

#ifdef M_DEBUG
	#define M_ENABLE_ASSERT
#endif

#ifdef M_ENABLE_ASSERT
	#define M_ASSERT(x, ...) if(!(x)) { M_ERROR("Assertion Error: {0}", __VA_ARGS__); __debugbreak();}
	#define M_CORE_ASSERT(x, ...) if(!(x)) { M_CORE_ERROR("Assertion Error: {0}", __VA_ARGS__); __debugbreak();}
#else
	#define M_ASSERT(x, ...)
	#define M_CORE_ASSERT(x, ...)
#endif

#define M_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Mawar
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}