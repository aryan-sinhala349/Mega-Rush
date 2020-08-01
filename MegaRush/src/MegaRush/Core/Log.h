#pragma once

#include "Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace MegaRush
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define MR_CORE_TRACE(...)    ::MegaRush::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MR_CORE_INFO(...)     ::MegaRush::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MR_CORE_WARN(...)     ::MegaRush::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MR_CORE_ERROR(...)    ::MegaRush::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MR_CORE_CRITICAL(...) ::MegaRush::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MR_TRACE(...)         ::MegaRush::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MR_INFO(...)          ::MegaRush::Log::GetClientLogger()->info(__VA_ARGS__)
#define MR_WARN(...)          ::MegaRush::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MR_ERROR(...)         ::MegaRush::Log::GetClientLogger()->error(__VA_ARGS__)
#define MR_CRITICAL(...)      ::MegaRush::Log::GetClientLogger()->critical(__VA_ARGS__)