#include "pch.h"
#include "Texture.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

#include "Vulkan/Utility/Commands/SingleTimeCommands.h"

namespace Ash::Vulkan
{
    Texture::Texture(const DefaultTexture& defaultTextureColor)
    {
        unsigned char pixelData[] = { 0, 0, 0, 1 };

        for (int i = 0; i < 3; i++)
        {
            pixelData[i] = (int)defaultTextureColor & (1 << i);
        }

        Texture(pixelData, 1, 1, 4, false);
    }

    Texture::Texture(VkImageCreateInfo imageInfo, VkImageViewCreateInfo viewInfo, VkMemoryPropertyFlags properties)
        : Width(imageInfo.extent.width), Height(imageInfo.extent.height), Extent2D{ Width, Height }, Extent3D(imageInfo.extent), Format(imageInfo.format)
    {
		static Context& context = Context::Get();

        VkResult result = vkCreateImage(context.Device, &imageInfo, nullptr, &Image);
        ASSERT(result == VK_SUCCESS, "Failed to create an image.");

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(context.Device, Image, &memRequirements);

        VkMemoryAllocateInfo allocInfo = Defaults<VkMemoryAllocateInfo>();
        {
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);
        }
        
        result = vkAllocateMemory(context.Device, &allocInfo, nullptr, &Memory);
        ASSERT(result == VK_SUCCESS, "Failed to allocate image memory.");

        result = vkBindImageMemory(context.Device, Image, Memory, 0);
        ASSERT(result == VK_SUCCESS, "Failed to bind image memory.");

		viewInfo.image = Image;
		viewInfo.format = Format;

        result = vkCreateImageView(context.Device, &viewInfo, nullptr, &View);
        ASSERT(result == VK_SUCCESS, "Failed to create an image view.");
    }

    Texture::Texture(const unsigned char* pixels, uint32_t width, uint32_t height, uint32_t channels, bool srgb, VkImageViewCreateInfo viewInfo)
        : Width(width), Height(height), Extent2D{ Width,Height }, Extent3D { Width, Height, 1 }
    {
        switch (channels)
        {
            case 1: Format = VK_FORMAT_R8_UNORM; break;
            case 2: Format = VK_FORMAT_R8G8_UNORM; break;
            case 3: Format = VK_FORMAT_R8G8B8_UNORM; break;
            case 4: Format = VK_FORMAT_R8G8B8A8_UNORM; break;
        }

        ASSERT(Format != VK_FORMAT_UNDEFINED, "Invalid number of channels. Can only be 1, 2, 3, or 4.");

        if (srgb)
        {
            // The difference between VK_FORMAT_..._UNORM and the associated VK_FORMAT_..._SRGB is +6
            Format = (VkFormat)(Format + 6);
        }

        VkImageCreateInfo imageInfo = Defaults<VkImageCreateInfo>();
        {
			imageInfo.format = Format;
			imageInfo.extent = Extent3D;
			imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        }

        Texture(imageInfo, viewInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        Transition(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        Buffer stagingBuffer(
            4, width * height,
            (void*)pixels,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

        CopyFromBuffer(stagingBuffer);

        Transition(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    Texture::~Texture()
    {
        static Context& context = Context::Get();

        vkDestroyImage(context.Device, Image, nullptr);
        vkDestroyImageView(context.Device, View, nullptr);
    }

    void Texture::Transition(VkImageLayout from, VkImageLayout to, VkCommandBuffer commandBuffer)
    {
        bool useSingleTimeCommand = commandBuffer == VK_NULL_HANDLE;

        if (useSingleTimeCommand)
        {
            commandBuffer = Utility::BeginSingleTimeCommands();
        }

        VkImageMemoryBarrier memoryBarrier = Defaults<VkImageMemoryBarrier>();
        {
			memoryBarrier.image = Image;
			memoryBarrier.oldLayout = from;
			memoryBarrier.newLayout = to;
        }

        VkPipelineStageFlags sourceStage{}, destinationStage{};

        switch (from)
        {
            case VK_IMAGE_LAYOUT_UNDEFINED:
            {
                memoryBarrier.srcAccessMask = NULL;
                sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                break;
            }
            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            case VK_IMAGE_LAYOUT_GENERAL:
            {
                memoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
                break;
            }
            default:
            {
                ASSERT(false, "Unsupported source layout for image transitions.");
            }
        }

        switch (to)
        {
            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            {
                memoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
                break;
            }
            case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_GENERAL:
            case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
            {
                memoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
                destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
                break;
            }
            default:
            {
                ASSERT(false, "Unsupported destination layout for image transitions.");
            }
        }

        vkCmdPipelineBarrier(
            commandBuffer,
            sourceStage, destinationStage,
            0,
            0, nullptr,
            0, nullptr,
            1, &memoryBarrier
        );

        if (useSingleTimeCommand)
        {
            Utility::EndSingleTimeCommands(commandBuffer);
        }
    }

    void Texture::CopyFromBuffer(const Buffer& buffer)
    {
        VkCommandBuffer commandBuffer = Utility::BeginSingleTimeCommands();

        VkBufferImageCopy region = Defaults<VkBufferImageCopy>();
        {
			region.imageExtent = Extent3D;
        }

        vkCmdCopyBufferToImage(
            commandBuffer,
            buffer,
            Image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region
        );

        Utility::EndSingleTimeCommands(commandBuffer);
    }

    uint32_t Texture::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
    {
		static Context& context = Context::Get();

        VkPhysicalDeviceMemoryProperties memoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(context.Device, &memoryProperties);

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

    VkImageViewCreateInfo DefaultImageView()
    {
        return Defaults<VkImageViewCreateInfo>();
    }
}