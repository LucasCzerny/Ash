#include "pch.h"
#include "Log.h"

namespace Ash
{
	LogLevel Log::s_LogLevel = LogLevel::ALL;

	void Log::SetLogLevel(const LogLevel& level)
	{
		s_LogLevel = level;
	}

	void Log::GenericLog()
	{
		std::cout << "\n";
	}
}