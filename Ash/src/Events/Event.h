#pragma once

#include "EventType.h"

namespace Ash
{
	class Event
	{
	public:
		template <typename T>
		T& Cast();

		virtual std::string GetName() const = 0;
		virtual EventType GetType() const = 0;

		bool HasType(EventType mask);
	};
}

#include "Event.inl"