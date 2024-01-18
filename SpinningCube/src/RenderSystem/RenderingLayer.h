#pragma once

#include <Ash.h>

#include "CubePipeline.h"

using namespace Ash;

namespace SpinningCube
{
	class RenderingLayer : public Layer
	{
	public:
		RenderingLayer();

		void OnUpdate() override;
		bool OnEvent(Event& event) override;

	private:
		EventType m_EventMask = EventType::KeyEvents;

		Vulkan::RenderSystem m_RenderSystem;

		Vulkan::Context& m_Context = Vulkan::Context::Get();
	};
}