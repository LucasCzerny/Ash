#include "pch.h"
#include "SwapChainTextures.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	SwapChainTexture::SwapChainTexture(VkImage image, VkFormat format, VkDevice device)
		: Image(image), m_Device(device)	
	{
		VkImageViewCreateInfo viewInfo = Defaults<VkImageViewCreateInfo>();
		{
			viewInfo.image = image;
			viewInfo.format = format;
		}

        VkResult result = vkCreateImageView(m_Device, &viewInfo, nullptr, &View);
        ASSERT(result == VK_SUCCESS, "Failed to create image view for a swap chain image.");
	}

	SwapChainDepthTexture::SwapChainDepthTexture(VkFormat depthFormat, VkDevice device, VkPhysicalDevice physicalDevice)
		: m_Device(device), m_PhysicalDevice(physicalDevice)
	{
		VkImageCreateInfo imageInfo = Defaults<VkImageCreateInfo>();
		{
			imageInfo.format = depthFormat;
			imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		}

		VkImageViewCreateInfo viewInfo = Defaults<VkImageViewCreateInfo>();
		{
			viewInfo.format = depthFormat;
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		}

        VkResult result = vkCreateImage(m_Device, &imageInfo, nullptr, &Image);
        ASSERT(result == VK_SUCCESS, "Failed to create an image.");

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(m_Device, Image, &memRequirements);

        VkMemoryAllocateInfo allocInfo = Defaults<VkMemoryAllocateInfo>();
        {
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        }
        
        result = vkAllocateMemory(m_Device, &allocInfo, nullptr, &Memory);
        ASSERT(result == VK_SUCCESS, "Failed to allocate image memory.");

        result = vkBindImageMemory(m_Device, Image, Memory, 0);
        ASSERT(result == VK_SUCCESS, "Failed to bind image memory.");

		viewInfo.image = Image;

        result = vkCreateImageView(m_Device, &viewInfo, nullptr, &View);
        ASSERT(result == VK_SUCCESS, "Failed to create an image view.");
	}

	uint32_t SwapChainDepthTexture::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
        VkPhysicalDeviceMemoryProperties memoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memoryProperties);

        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        {
            if ((typeFilter) & (1 << i) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            {
                return i;
            }
        }

        ASSERT(false, "Failed to find a supported memory type.");
        return 0;
	}
}
