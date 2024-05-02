#pragma once

#include "Vulkan/Buffer/Buffer.h"
#include "Vulkan/Context/Context.h"

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
		Texture();
		Texture(VkImage image, VkImageView view, VkDeviceMemory memory, uint32_t width, uint32_t height, VkFormat format);

		Texture(const DefaultTexture& defaultTextureColor);

		Texture(VkImageCreateInfo imageInfo, VkImageViewCreateInfo viewInfo = DefaultImageView(), VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		Texture(const unsigned char* pixels, uint32_t width, uint32_t height, uint32_t channels, bool srgb = false, VkImageViewCreateInfo viewInfo = DefaultImageView());

		~Texture();

		Texture(const Texture& texture);
		Texture(Texture&& texture) noexcept;
		Texture& operator=(const Texture& texture);
		Texture& operator=(Texture&& texture) noexcept;

		void Reset();
		bool IsEmpty() const { return Image == VK_NULL_HANDLE; }

		void Transition(VkImageLayout from, VkImageLayout to, VkCommandBuffer commandBuffer = VK_NULL_HANDLE);
		void CopyFromBuffer(const Buffer& buffer);

		VkImage* Pointer() { return &Image; }
		const VkImage* Pointer() const { return (const VkImage*)&Image; }

		operator VkImage() const { return Image; }

		operator bool() const { return IsEmpty(); }

	private:
		std::shared_ptr<Context> m_Context = nullptr;

	private:
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}