#pragma once

#include "Event.h"

namespace Ash
{
	struct EventFunction
	{
	public:
		std::function<bool(Event&)> Function;
		int Precedence = 0;

	public:
		EventFunction(std::function<bool(Event&)> function, int precedence = 0)
			: Function(function), Precedence(precedence) {}

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
