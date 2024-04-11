#pragma once

#include "Event.h"

namespace Ash
{
	struct EventFunction
	{
		std::function<bool(Event&)> Function;
		int Precendence = 0;

		bool Call(Event& event);

		static bool Compare(const EventFunction& first, const EventFunction& second);
	};

	class EventDispatcher
	{
	public:
		static void Subscribe(const EventFunction& eventFunction);
		static void Dispatch(Event& event);

	private:
		static std::vector<EventFunction> s_EventFunctions; 
	};
}
