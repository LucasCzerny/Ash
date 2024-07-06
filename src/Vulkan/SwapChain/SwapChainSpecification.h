#pragma once

namespace Ash::Vulkan
{
	struct SwapChainSpecification
	{
		VkExtent2D Extent;
		VkPresentModeKHR PresentMode;
		VkSurfaceFormatKHR SurfaceFormat;
		uint32_t ImageCount;
		VkFormat DepthFormat;
	};
}