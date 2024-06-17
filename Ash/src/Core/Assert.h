#pragma once

#include "Log.h"

#if defined(ASH_DEBUG) && defined(ASH_PLATFORM_WINDOWS)
	#define ASSERT(condition, ...) if (!(condition)) { Log::Error(__VA_ARGS__); __debugbreak(); }
#elif defined(ASH_DEBUG) && defined(ASH_PLATFORM_LINUX)
	#define ASSERT(condition, ...) if (!(condition)) { Log::Error(__VA_ARGS__); raise(SIGTRAP); }
#else
	#define ASSERT(...)
#endif
