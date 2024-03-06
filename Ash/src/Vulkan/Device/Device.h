#pragma once

#include "Queue.h"
#include "SwapChainSupportDetails.h"

namespace Ash::Vulkan
{
	class Device
	{
	public:
		VkDevice Logical;
		VkPhysicalDevice Physical;

		Queue GraphicsQueue{}, PresentQueue{};

		DeviceSwapChainSupport SwapChainSupport;

	public:
		Device();

		Device(const Device&) = delete;
		void operator=(const Device&) = delete;
		Device(Device&&) = delete;
		Device& operator=(Device&&) = delete;

		operator VkDevice() const { return Logical; }
		operator VkPhysicalDevice() const { return Physical; }

	private:
		void ChoosePhysicalDevice();
		std::array<uint32_t, 2> GetQueueFamilies(VkPhysicalDevice device);
		DeviceSwapChainSupport QuerySwapChainSupport(VkPhysicalDevice device);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		bool SupportsRequiredExtensions(VkPhysicalDevice device);
		bool SupportsAnisotropicSampling(VkPhysicalDevice device);

		void ChooseLogicalDevice();

		void GetQueues();
	};
}