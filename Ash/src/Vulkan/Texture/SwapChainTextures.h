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
		SwapChainTexture(VkImage image, VkFormat format, VkDevice device);

	private:
		VkDevice m_Device = VK_NULL_HANDLE;
	};

	class SwapChainDepthTexture
	{
	public:
		VkImage Image = VK_NULL_HANDLE;
		VkImageView View = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;

	public:
		SwapChainDepthTexture() = default;
		SwapChainDepthTexture(VkFormat depthFormat, VkDevice device, VkPhysicalDevice physicalDevice);

	private:
		VkDevice m_Device = VK_NULL_HANDLE;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

	private:
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}

