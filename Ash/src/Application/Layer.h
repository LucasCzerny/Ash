#pragma once

#include "Events/Event.h"
#include "Scene/Scene.h"

namespace Ash
{
	class Layer
	{
	public:
		Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update(float deltaTime) {}
		virtual void Draw() {}
		virtual bool OnEvent(Event& event) { return false; }

		bool operator==(Layer& other) const;

	private:
		uint8_t m_Id;
	};
}