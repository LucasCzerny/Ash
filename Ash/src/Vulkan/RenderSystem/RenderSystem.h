#pragma once

#include "Pipeline.h"

#include "Scene/Scene.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	class RenderSystem
	{
	public:
		RenderSystem() = default;

		RenderSystem(const std::vector<Pipeline>& pipelines);
		~RenderSystem();
		
		void Draw();

	private:
		std::vector<Pipeline> m_Pipelines;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderingFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;

	protected:
		float m_LastResizeTime = 0.0f;
		std::shared_ptr<Context> m_Context = nullptr;

	protected:
		virtual void OnSwapChainRecreation() {}

	private:
		void CreateSyncObjects();

		uint32_t AquireNextImage(uint32_t currentFrame);
		VkResult SubmitCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex);
	};
}
