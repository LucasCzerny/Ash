#include "pch.h"
#include "SwapChain.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"
#include "Vulkan/Texture/Texture.h"

namespace Ash::Vulkan
{
	SwapChain::SwapChain()
	{	
		Recreate();
	}

	void SwapChain::Recreate()
	{
		static Context& context = Context::Get();

		m_OldSwapChain = Handle;

		vkDeviceWaitIdle(context.Device);

		ChooseSwapChainSpecification();

		CreateSwapChain();

		CreateSwapChainImages();
		CreateDepthResources();
	}

	void SwapChain::ChooseSwapChainSpecification()
	{
		static Context& context = Context::Get();

		VkExtent2D windowExtent = context.Window.Extent2D;

		while (windowExtent.width == 0 || windowExtent.height == 0)
		{
			windowExtent = context.Window.Extent2D;
			glfwWaitEvents();
		}

		DeviceSwapChainSupport supportDetails = context.Device.SwapChainSupport;

		Extent2D = ChooseExtent(supportDetails.Capabilities, windowExtent);
		Extent3D = { Extent2D.width, Extent3D.height, 1 };
		PresentMode = ChoosePresentMode(supportDetails.PresentModes);
		SurfaceFormat = ChooseSwapChainSurfaceFormat(supportDetails.SurfaceFormats);

		uint32_t imageCount = context.Device.SwapChainSupport.Capabilities.minImageCount + 1;
		uint32_t maxImageCount = context.Device.SwapChainSupport.Capabilities.maxImageCount;

		if (maxImageCount > 0 && imageCount > maxImageCount)
		{
			imageCount = maxImageCount;
		}

		ImageCount = imageCount;

		VkFormat depthFormats[3] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
		VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
		VkFormatFeatureFlags formatFeatures = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;

		for (VkFormat format : depthFormats)
		{
			VkFormatProperties formatProperties;
			vkGetPhysicalDeviceFormatProperties(context.Device, format, &formatProperties);

			if (formatProperties.optimalTilingFeatures & formatFeatures)
			{
				DepthFormat = format;
				return;
			}
		}

		ASSERT(false, "Failed to find an appropiate depth format.");
	}

	VkExtent2D SwapChain::ChooseExtent(const VkSurfaceCapabilitiesKHR & surfaceCapabilities, VkExtent2D default)
	{
		if (surfaceCapabilities.currentExtent.height != UINT32_MAX)
		{
			return surfaceCapabilities.currentExtent;
		}

		return default;
	}

	VkPresentModeKHR SwapChain::ChoosePresentMode(const std::vector<VkPresentModeKHR>& availableModes)
	{
		// Choose Mailbox if available, else just default to Fifo

		for (const auto& presentMode : availableModes)
		{
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return presentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		// Choose SRGB if available, else just default to the first format in the vector

		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	void SwapChain::CreateSwapChain()
	{
		static Context& context = Context::Get();
		static Device& device = context.Device;

		VkSwapchainCreateInfoKHR createInfo = Defaults<VkSwapchainCreateInfoKHR>();
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (device.GraphicsQueue.Family == device.PresentQueue.Family)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}
		else
		{
			uint32_t queueFamilyIndices[2] = { device.GraphicsQueue.Family, device.PresentQueue.Family };

			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}

		createInfo.oldSwapchain = m_OldSwapChain;

		VkResult result = vkCreateSwapchainKHR(context.Device, &createInfo, nullptr, &Handle);
	}

	void SwapChain::CreateSwapChainImages()
	{
		static Context& context = Context::Get();

		vkGetSwapchainImagesKHR(context.Device, Handle, &ImageCount, nullptr);

		std::vector<VkImage> imageHandles(ImageCount);
		VkResult result = vkGetSwapchainImagesKHR(context.Device, Handle, &ImageCount, imageHandles.data());

		ASSERT(result == VK_SUCCESS, "Failed to get the swap chain images.");

		for (uint32_t i = 0; i < ImageCount; i++)
		{
			Images.emplace_back(imageHandles[i], SurfaceFormat.format, Extent2D);
		}
	}

	void SwapChain::CreateDepthResources()
	{
		static Context& context = Context::Get();

		for (uint32_t i = 0; i < ImageCount; i++)
		{
			VkImageCreateInfo imageInfo = Defaults<VkImageCreateInfo>();
			imageInfo.format = DepthFormat;
			imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

			VkImageViewCreateInfo viewInfo = Defaults<VkImageViewCreateInfo>();
			viewInfo.format = DepthFormat;
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

			DepthImages.emplace_back(imageInfo, viewInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		}
	}
}