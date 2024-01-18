#pragma once

#include "Event.h"

namespace Ash
{
	class WindowCloseEvent : public Event
	{
	public:
		std::string GetName() const override { return "Window Close Event"; }
		EventType GetType() const override { return EventType::WindowClose; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		uint32_t Width, Height;

	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: Width(width), Height(height) {}

		std::string GetName() const override { return "Window Resize Event"; }
		EventType GetType() const override { return EventType::WindowResize; }
	};

	class WindowFocusEvent : public Event
	{

	public:
		std::string GetName() const override { return "Window Focus Event"; }
		EventType GetType() const override { return EventType::WindowFocus; }
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		std::string GetName() const override { return "Window Lost Focus Event"; }
		EventType GetType() const override { return EventType::WindowLostFocus; }

	};

	class WindowMovedEvent : public Event
	{
	public:
		std::string GetName() const override { return "Window Moved Event"; }
		EventType GetType() const override { return EventType::WindowMoved; }
	};
}
