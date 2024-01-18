#include "pch.h"
#include "SwapChain.h"

#include "Vulkan/Defaults.h"
#include "Vulkan/Context/Context.h"
#include "Vulkan/Texture/Texture.h"

namespace Ash::Vulkan
{
	SwapChain::SwapChain()
        : m_Context(Context::Get())
	{	
		Recreate();
	}

	void SwapChain::Recreate()
	{
		m_OldSwapChain = Handle;

		vkDeviceWaitIdle(m_Context.Device);

		ChooseSwapChainSpecification();

		CreateSwapChain();

		CreateSwapChainImages();
		CreateSwapChainImageViews();
		CreateDepthResources();
	}

	void SwapChain::ChooseSwapChainSpecification()
	{
		VkExtent2D windowExtent = m_Context.Window.GetExtent2D();

		while (windowExtent.width == 0 || windowExtent.height == 0)
		{
			windowExtent = m_Context.Window.GetExtent2D();
			glfwWaitEvents();
		}

		DeviceSwapChainSupport supportDetails = m_Context.Device.SwapChainSupport;

		Extent = ChooseExtent(supportDetails.Capabilities, windowExtent);
		PresentMode = ChoosePresentMode(supportDetails.PresentModes);
		SurfaceFormat = ChooseSwapChainSurfaceFormat(supportDetails.SurfaceFormats);

		uint32_t imageCount = m_Context.Device.SwapChainSupport.Capabilities.minImageCount + 1;
		uint32_t maxImageCount = m_Context.Device.SwapChainSupport.Capabilities.maxImageCount;

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
			vkGetPhysicalDeviceFormatProperties(m_Context.Device, format, &formatProperties);

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
		static Device& device = m_Context.Device;

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

		VkResult result = vkCreateSwapchainKHR(m_Context.Device, &createInfo, nullptr, &Handle);
	}

	void SwapChain::CreateSwapChainImages()
	{
		vkGetSwapchainImagesKHR(m_Context.Device, Handle, &ImageCount, nullptr);
		Images.resize(ImageCount);
		VkResult result = vkGetSwapchainImagesKHR(m_Context.Device, Handle, &ImageCount, Images.data());

		ASSERT(result == VK_SUCCESS, "Failed to get the swap chain images.");
	}

	void SwapChain::CreateSwapChainImageViews()
	{
		// TODO
		ImageViews.resize(Images.size());

		for (size_t i = 0; i < Images.size(); i++)
		{
			VkImageViewCreateInfo viewInfo{};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

			viewInfo.image = Images[i];
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = SurfaceFormat.format;

			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = 1;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;

			VkResult result = vkCreateImageView(m_Context.Device, &viewInfo, nullptr, &Images[i].View);
			ASSERT(result == VK_SUCCESS, "Failed to create a swap chain image view.");
		}
	}

	void SwapChain::CreateDepthResources()
	{
		uint32_t imageCount = ImageCount;

		for (uint32_t i = 0; i < imageCount; i++)
		{
			VkImageCreateInfo imageInfo = Defaults<VkImageCreateInfo>();
			imageInfo.format = DepthFormat;
			imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

			DepthImages.emplace_back(imageInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			VkImageViewCreateInfo viewInfo = Defaults<VkImageViewCreateInfo>();
			viewInfo.image = DepthImages[0];
			viewInfo.format = DepthFormat;
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

			VkResult result = vkCreateImageView(m_Context.Device, &viewInfo, nullptr, &DepthImages[i].View);
			ASSERT(result == VK_SUCCESS, "Failed to create a depth image view.");
		}
	}
}