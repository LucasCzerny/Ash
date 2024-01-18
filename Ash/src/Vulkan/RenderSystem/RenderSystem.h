#pragma once

#include "Pipeline.h"

#include "Scene/Scene.h"

namespace Ash::Vulkan
{
	class RenderSystem
	{
	public:
		RenderSystem(const std::vector<Pipeline>& pipelines)
			: m_Pipelines(pipelines) {}

		~RenderSystem();
		
		// Not copyable or moveable
		RenderSystem(const RenderSystem&) = delete;
		void operator=(const RenderSystem&) = delete;
		RenderSystem(RenderSystem&&) = delete;
		RenderSystem& operator=(RenderSystem&&) = delete;

		void DrawScene(const Scene& scene);

	private:
		std::vector<Pipeline> m_Pipelines;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderingFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;
		
		Context& m_Context = Context::Get();

	protected:
		float m_LastResizeTime = 0.0f;

	protected:
		virtual void OnSwapChainRecreation() {}

	private:
		void CreateSyncObjects();

		uint32_t AquireNextImage(uint32_t currentFrame);
		VkResult SubmitCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex);
	};
}