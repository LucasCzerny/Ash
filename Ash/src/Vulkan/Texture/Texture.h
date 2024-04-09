#pragma once

#include "Vulkan/Buffer/Buffer.h"

namespace Ash::Vulkan
{
	static VkImageViewCreateInfo DefaultImageView();

	enum class DefaultTexture
	{
		BLACK = 0,
		RED = 1 << 0,
		BLUE = 1 << 1,
		GREEN = 1 << 2,
		WHITE = 0b111
	};

	struct Texture
	{
	public:
		VkImage Image = VK_NULL_HANDLE;
		VkImageView View = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;

		uint32_t Width = 0, Height = 0;
		VkExtent2D Extent2D = { 0, 0 };
		VkExtent3D Extent3D = { 0, 0, 0 };

		VkFormat Format = VK_FORMAT_UNDEFINED;

	public:
		Texture() = default;
		Texture(VkImage image, VkImageView view, VkDeviceMemory memory, uint32_t width, uint32_t height, VkFormat format)
			: Image(image), View(view), Memory(memory), Width(width), Height(height), Extent2D{ width, height }, Extent3D{ width, height, 1 }, Format(format) {}

		Texture(const DefaultTexture& defaultTextureColor);

		Texture(VkImageCreateInfo imageInfo, VkImageViewCreateInfo viewInfo = DefaultImageView(), VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		Texture(const unsigned char* pixels, uint32_t width, uint32_t height, uint32_t channels, bool srgb = false, VkImageViewCreateInfo viewInfo = DefaultImageView());

		~Texture();

		// Not copyable or moveable
		// Texture(const Texture&) = delete;
		// void operator=(const Texture&) = delete;
		// Texture(Texture&&) = delete;
		// Texture& operator=(Texture&&) = delete;

		void Transition(VkImageLayout from, VkImageLayout to, VkCommandBuffer commandBuffer = VK_NULL_HANDLE);
		void CopyFromBuffer(const Buffer& buffer);

		operator VkImage() const { return Image; }

	private:
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}