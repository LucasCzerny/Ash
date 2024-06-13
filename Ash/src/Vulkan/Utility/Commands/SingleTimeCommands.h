#pragma once

namespace Ash::Vulkan::Utility
{
	VkCommandBuffer BeginSingleTimeCommands();
	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
}
