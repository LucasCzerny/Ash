namespace Ash
{
	template <typename... Args>
	void Log::Info(const Args&... args)
	{
		if (s_LogLevel > LogLevel::ALL)
		{
			return;
		}

		std::cout << "[INFO] ";
		GenericLog(args...);
	}

	template <typename... Args>
	void Log::Warn(const Args&... args)
	{
		if (s_LogLevel > LogLevel::WARN)
		{
			return;
		}

		std::cout << "[WARNING] ";
		GenericLog(args...);
	}

	template <typename... Args>
	void Log::Error(const Args&... args)
	{
		if (s_LogLevel > LogLevel::ERROR)
		{
			return;
		}

		std::cout << "[ERROR] ";
		GenericLog(args...);
	}

	template <typename Type, typename... Other>
	void Log::GenericLog(const Type& first, const Other&... other)
	{
		std::cout << first;

		GenericLog(other...);
	}
}