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
		SwapChainTexture(VkImage image, VkFormat format);
	};

	class SwapChainDepthTexture
	{
	public:
		VkImage Image = VK_NULL_HANDLE;
		VkImageView View = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;

	public:
		SwapChainDepthTexture() = default;
		SwapChainDepthTexture(VkFormat depthFormat);

	private:
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}

