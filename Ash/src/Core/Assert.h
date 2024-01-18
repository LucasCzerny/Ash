#pragma once

#include "Log.h"

#ifdef ASH_DEBUG
	#define ASSERT(condition, ...) if (!(condition)) { Log::Error(__VA_ARGS__); __debugbreak(); }
#else
	#define ASSERT(...)
#endif