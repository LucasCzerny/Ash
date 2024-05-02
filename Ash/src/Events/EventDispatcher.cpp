#include "pch.h"
#include "EventDispatcher.h"

namespace Ash
{
	std::vector<EventFunction> EventDispatcher::s_EventFunctions; 
		
	bool EventFunction::Call(Event& event)
	{
		return Function(event);
	}

	bool EventFunction::Compare(const EventFunction& first, const EventFunction& second)
	{
		return first.Precedence >= second.Precedence;
	}

	void EventDispatcher::Subscribe(const EventFunction& eventFunction)
	{
		auto it = std::lower_bound(s_EventFunctions.begin(), s_EventFunctions.end(), eventFunction, EventFunction::Compare);
		s_EventFunctions.insert(it, eventFunction);
	}

	void EventDispatcher::Dispatch(Event& event)
	{
		for (EventFunction& eventFunction : s_EventFunctions)
		{
			bool handled = eventFunction.Call(event);

			if (handled)
			{
				break;
			}
		}
	}
}
