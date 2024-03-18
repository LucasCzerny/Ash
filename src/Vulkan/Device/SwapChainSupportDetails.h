#pragma once

namespace Ash::Vulkan
{
	struct DeviceSwapChainSupport
	{
		VkSurfaceCapabilitiesKHR Capabilities;
		std::vector<VkSurfaceFormatKHR> SurfaceFormats;
		std::vector<VkPresentModeKHR> PresentModes;

		bool IsComplete() const
		{
			return !SurfaceFormats.empty() && !PresentModes.empty();
		}
	};
}