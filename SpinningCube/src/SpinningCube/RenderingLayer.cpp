#include "pch.h"
#include "RenderingLayer.h"

#include "Vulkan/Defaults.h"

namespace SpinningCube
{
	RenderingLayer::RenderingLayer()
		: m_RenderSystem({
			{ CubePipeline::CreateConfig(), CubePipeline::Record }
		})
	{
		Entity cameraEntity = m_Scene.CreateEntity("Camera");
		cameraEntity.AddComponent<CameraComponent>();
		cameraEntity.AddComponent<BasicMovementComponent>();
	}

    void RenderingLayer::Update(float deltaTime)
    {
		static unsigned int frameCounter = 0;

		if (frameCounter++ % 10000 == 0)
		{
			Log::Info(1.0f / deltaTime);
		}
    }

	void RenderingLayer::Draw()
	{
		m_RenderSystem.DrawScene(m_Scene);
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
