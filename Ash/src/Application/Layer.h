#pragma once

#include "Events/Event.h"

namespace Ash
{
	class Layer
	{
	public:
		Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual bool OnEvent(Event& event) { return false; }

		bool operator==(Layer& other) const;

	private:
		uint8_t m_Id;
	};
}