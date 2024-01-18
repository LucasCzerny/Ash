#pragma once

namespace Ash
{
	enum class LogLevel
	{
		ALL, WARN, ERROR
	};

	class Log
	{
	public:
		template <typename... Args>
		static void Info(const Args&... args);

		template <typename... Args>
		static void Warn(const Args&... args);

		template <typename... Args>
		static void Error(const Args&... args);

		static void SetLogLevel(const LogLevel& level);

	private:
		static LogLevel s_LogLevel;

	private:
		template <typename Type, typename... Other>
		static void GenericLog(const Type& first, const Other&... other);

		static void GenericLog();
	};
}

#include "Log.inl"