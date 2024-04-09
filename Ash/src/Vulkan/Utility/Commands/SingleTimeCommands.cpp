#include "pch.h"
#include "SingleTimeCommands.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan::Utility
{
	VkCommandBuffer BeginSingleTimeCommands()
	{
		Context& context = Context::Get();

		VkCommandBufferAllocateInfo allocInfo = Defaults<VkCommandBufferAllocateInfo>();
		{
			allocInfo.commandBufferCount = 1;
		}

		VkCommandBuffer commandBuffer;
		VkResult result = vkAllocateCommandBuffers(context.Device, &allocInfo, &commandBuffer);

		ASSERT(result == VK_SUCCESS, "Failed to allocate a single time command buffer.");

		VkCommandBufferBeginInfo beginInfo = Defaults<VkCommandBufferBeginInfo>();
		{
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		}

		result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
		ASSERT(result == VK_SUCCESS, "Failed to begin a single time command buffer.");

		return commandBuffer;
	}

	void EndSingleTimeCommands(VkCommandBuffer commandBuffer)
	{
		Context& context = Context::Get();

		VkResult result = vkEndCommandBuffer(commandBuffer);
		ASSERT(result == VK_SUCCESS, "Failed to end a single time command buffer.");

		VkSubmitInfo submitInfo{};
		{
			submitInfo.commandBufferCount = 0;
			submitInfo.pCommandBuffers = nullptr;
		}

		vkQueueSubmit(context.Device.GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(context.Device.GraphicsQueue);

		vkFreeCommandBuffers(context.Device, context.CommandPool, 1, &commandBuffer);
	}
}
