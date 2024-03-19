#include "pch.h"
#include "SwapChainTexture.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	SwapChainTexture::SwapChainTexture(VkImage image, VkFormat format, VkExtent2D extent2D)
		: Image(image)
	{
		static Context& context = Context::Get();

		VkImageViewCreateInfo viewInfo = Defaults<VkImageViewCreateInfo>();
		{
			viewInfo.image = image;
			viewInfo.format = format;
		}

        VkResult result = vkCreateImageView(context.Device, &viewInfo, nullptr, &View);
        ASSERT(result == VK_SUCCESS, "Failed to create image view for a swap chain image.");
	}
}
