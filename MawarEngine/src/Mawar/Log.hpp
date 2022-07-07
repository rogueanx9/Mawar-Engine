#pragma once

#include "Core.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Mawar 
{
	class M_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define M_CORE_TRACE(...)      ::Mawar::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define M_CORE_INFO(...)       ::Mawar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define M_CORE_WARN(...)       ::Mawar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define M_CORE_ERROR(...)      ::Mawar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define M_CORE_FATAL(...)      ::Mawar::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define M_TRACE(...)           ::Mawar::Log::GetClientLogger()->trace(__VA_ARGS__)
#define M_INFO(...)            ::Mawar::Log::GetClientLogger()->info(__VA_ARGS__)
#define M_WARN(...)            ::Mawar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define M_ERROR(...)           ::Mawar::Log::GetClientLogger()->error(__VA_ARGS__)
#define M_FATAL(...)           ::Mawar::Log::GetClientLogger()->fatal(__VA_ARGS__)