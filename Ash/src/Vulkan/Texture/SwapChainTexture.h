#pragma once

namespace Ash::Vulkan
{
	class SwapChainTexture
	{
	public:
		VkImage Image = VK_NULL_HANDLE;
		VkImageView View = VK_NULL_HANDLE;

	public:
		SwapChainTexture() = default;
		SwapChainTexture(VkImage image, VkFormat format, VkExtent2D extent2D);
	};
}

