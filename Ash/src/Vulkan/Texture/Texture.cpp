#include "pch.h"
#include "Texture.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

#include "Vulkan/Utility/Commands/SingleTimeCommands.h"

namespace Ash::Vulkan
{
    Texture::Texture(VkImage image, VkImageView view, VkDeviceMemory memory, uint32_t width, uint32_t height, VkFormat format)
		: m_Context(Context::Get()), Image(image), View(view), Memory(memory), Width(width), Height(height), Extent2D{ width, height }, Extent3D{ width, height, 1 }, Format(format) {}

    Texture::Texture(const DefaultTexture& defaultTextureColor)
        : m_Context(Context::Get())
    {
        unsigned char pixelData[] = { 0, 0, 0, 1 };

        for (int i = 0; i < 3; i++)
        {
            pixelData[i] = (int)defaultTextureColor & (1 << i);
        }

        *this = Texture(pixelData, 1, 1, 4, false);
    }

    Texture::Texture(VkImageCreateInfo imageInfo, VkImageViewCreateInfo viewInfo, VkMemoryPropertyFlags properties)
        : m_Context(Context::Get()), Width(imageInfo.extent.width), Height(imageInfo.extent.height), Extent2D{ Width, Height }, Extent3D(imageInfo.extent), Format(imageInfo.format)
    {
        VkResult result = vkCreateImage(m_Context->Device, &imageInfo, nullptr, &Image);
        ASSERT(result == VK_SUCCESS, "Failed to create an image.");

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(m_Context->Device, Image, &memRequirements);

        VkMemoryAllocateInfo allocInfo = Defaults<VkMemoryAllocateInfo>();
        {
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);
        }
        
        result = vkAllocateMemory(m_Context->Device, &allocInfo, nullptr, &Memory);
        ASSERT(result == VK_SUCCESS, "Failed to allocate image memory.");

        result = vkBindImageMemory(m_Context->Device, Image, Memory, 0);
        ASSERT(result == VK_SUCCESS, "Failed to bind image memory.");

		viewInfo.image = Image;
		viewInfo.format = Format;

        result = vkCreateImageView(m_Context->Device, &viewInfo, nullptr, &View);
        ASSERT(result == VK_SUCCESS, "Failed to create an image view.");
    }

    Texture::Texture(const unsigned char* pixels, uint32_t width, uint32_t height, uint32_t channels, bool srgb, VkImageViewCreateInfo viewInfo)
        : m_Context(Context::Get()), Width(width), Height(height), Extent2D{ Width,Height }, Extent3D { Width, Height, 1 }
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

        *this = Texture(imageInfo, viewInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

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
        vkDestroyImage(m_Context->Device, Image, nullptr);
        vkDestroyImageView(m_Context->Device, View, nullptr);
    }

    Texture::Texture(const Texture& texture)
        : Texture(texture.Image, texture.View, texture.Memory, texture.Width, texture.Height, texture.Format)
    {
		Log::Info("Texture was just copied at line ", __LINE__, " in file ", __FILE__);
    }

    Texture::Texture(Texture&& texture) noexcept
        : Texture(texture.Image, texture.View, texture.Memory, texture.Width, texture.Height, texture.Format)
    {
        texture.Reset();
    }

    Texture& Texture::operator=(const Texture& texture)
    {
        *this = Texture(texture.Image, texture.View, texture.Memory, texture.Width, texture.Height, texture.Format);
		Log::Info("Texture was just copied at line ", __LINE__, " in file ", __FILE__);

        return *this;
    }

    Texture& Texture::operator=(Texture&& texture) noexcept
    {
		Image = texture.Image;
		View = texture.View;
		Memory = texture.Memory;

        Width = texture.Width, Height = texture.Height;
		Extent2D = texture.Extent2D;
        Extent3D = texture.Extent3D;
        
        Format = texture.Format;

        return *this;
    }

    void Texture::Reset()
    {
		Image = VK_NULL_HANDLE;
		View = VK_NULL_HANDLE;
		Memory = VK_NULL_HANDLE;

		Width = 0, Height = 0;
		Extent2D = { 0, 0 };
		Extent3D = { 0, 0, 0 };

		Format = VK_FORMAT_UNDEFINED;
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
        VkPhysicalDeviceMemoryProperties memoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(m_Context->Device, &memoryProperties);

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