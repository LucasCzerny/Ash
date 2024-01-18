#include "pch.h"
#include "RenderingLayer.h"

#include "Vulkan/Defaults.h"

namespace SpinningCube
{
	RenderingLayer::RenderingLayer()
		: m_RenderSystem({
			{ CubePipeline::CreatePipelineConfig(), CubePipeline::Record }
		})
	{}

    void RenderingLayer::OnUpdate()
    {
    }

    bool RenderingLayer::OnEvent(Event& event)
    {
		if (!event.HasType(m_EventMask))
		{
			return false;
		}

		switch (event.GetType())
		{
			case EventType::KeyPress:
			{
				break;
			}
		}

		return true;
    }
}
