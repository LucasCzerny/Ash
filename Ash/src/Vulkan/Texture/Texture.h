#pragma once

#include "Vulkan/Buffer/Buffer.h"

namespace Ash::Vulkan
{
	class Context;

	struct Texture
	{
	public:
		VkImage Image = VK_NULL_HANDLE;
		VkImageView View = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;

		uint32_t Width = 0, Height = 0;
		VkExtent3D Extent = { 0, 0, 0 };

		VkFormat Format = VK_FORMAT_UNDEFINED;

	public:
		Texture() = default;
		Texture(const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		Texture(const unsigned char* pixels, uint32_t width, uint32_t height, uint32_t channels, bool srgb = false);

		~Texture();

		// Not copyable or moveable
		Texture(const Texture&) = delete;
		void operator=(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(Texture&&) = delete;

		void Transition(VkImageLayout from, VkImageLayout to, VkCommandBuffer commandBuffer = VK_NULL_HANDLE);
		void CopyFromBuffer(const Buffer& buffer);

		operator VkImage() const { return Image; }

	private:
		VkMemoryAllocateFlagBits m_MemoryFlags;

		Context& m_Context;
		
	private:
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}