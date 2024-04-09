#include "pch.h"
#include "RenderSystem.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	static Context& context = Context::Get();

	RenderSystem::RenderSystem(const std::vector<Pipeline>& pipelines)
		: m_Pipelines(pipelines)
	{
		CreateSyncObjects();
	}
		
	RenderSystem::~RenderSystem()
	{
		static const uint32_t maxFramesInFlight = Config::Get().MaxFramesInFlight;

		for (uint32_t i = 0; i < maxFramesInFlight; i++)
		{
			vkDestroySemaphore(context.Device, m_RenderingFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(context.Device, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroyFence(context.Device, m_InFlightFences[i], nullptr);
		}
	}

	void RenderSystem::DrawScene(Scene& scene)
	{
		static const uint32_t maxFramesInFlight = Config::Get().MaxFramesInFlight;
		static uint32_t currentFrame = 0;

		VkCommandBuffer commandBuffer = context.CommandBuffers[currentFrame];
		uint32_t imageIndex = AquireNextImage(currentFrame);

		if (imageIndex == UINT32_MAX)
		{
			context.SwapChain.Recreate();
			OnSwapChainRecreation();

			Log::Info("Swap Chain is being recreated because it was out of date.");
			return;
		}

		vkWaitForFences(context.Device, 1, &m_InFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
		vkResetFences(context.Device, 1, &m_InFlightFences[currentFrame]);

		for (const Pipeline& pipeline : m_Pipelines)
		{
			pipeline.RecordCommandBuffer(commandBuffer, currentFrame, imageIndex, scene);
		}

		VkResult result = SubmitCommandBuffer(commandBuffer, currentFrame, imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		{
			context.SwapChain.Recreate();
			OnSwapChainRecreation();

			Log::Info("Swap Chain is being recreated because it was out of date or suboptimal.");
		}
		else
		{
			ASSERT(result == VK_SUCCESS, "Failed to present swap chain image");
		}

		currentFrame = (currentFrame + 1) % maxFramesInFlight;
	}

	void RenderSystem::CreateSyncObjects()
	{
		static uint32_t maxFramesInFlight = Config::Get().MaxFramesInFlight;

		m_ImageAvailableSemaphores.resize(maxFramesInFlight);
		m_RenderingFinishedSemaphores.resize(maxFramesInFlight);
		m_InFlightFences.resize(maxFramesInFlight);
		// m_ImagesInFlight.resize(maxFramesInFlight);

		VkSemaphoreCreateInfo semaphoreInfo = Defaults<VkSemaphoreCreateInfo>();

		VkFenceCreateInfo fenceInfo = Defaults<VkFenceCreateInfo>();
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (uint32_t i = 0; i < maxFramesInFlight; i++)
		{
			VkResult result = (VkResult)(
				vkCreateSemaphore(context.Device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) +
				vkCreateSemaphore(context.Device, &semaphoreInfo, nullptr, &m_RenderingFinishedSemaphores[i]) +
				vkCreateFence(context.Device, &fenceInfo, nullptr, &m_InFlightFences[i])
			);

			ASSERT(result == VK_SUCCESS, "Failed to create the synchronization objects.");
		}
	}

	uint32_t RenderSystem::AquireNextImage(uint32_t currentFrame)
	{
		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(context.Device, context.SwapChain, UINT64_MAX, m_ImageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			return UINT32_MAX;
		}

		ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "Failed to acquire swap chain image");

		return imageIndex;
	}

	VkResult RenderSystem::SubmitCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex)
	{
		VkSubmitInfo submitInfo = Defaults<VkSubmitInfo>();
		{
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = &m_ImageAvailableSemaphores[currentFrame];

			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &commandBuffer;

			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = &m_RenderingFinishedSemaphores[currentFrame];
		}

		VkResult result = vkQueueSubmit(context.Device.GraphicsQueue, 1, &submitInfo, m_InFlightFences[currentFrame]);
		ASSERT(result == VK_SUCCESS, "Failed to submit a command buffer to the graphics queue.");

		VkPresentInfoKHR presentInfo = Defaults<VkPresentInfoKHR>();
		{
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = &m_RenderingFinishedSemaphores[currentFrame];

			presentInfo.pImageIndices = &imageIndex;
		}

		result = vkQueuePresentKHR(context.Device.GraphicsQueue, &presentInfo);
		
		return result;
	}
}
