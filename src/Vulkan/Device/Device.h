#pragma once

#include "Queue.h"
#include "SwapChainSupportDetails.h"

#include "Vulkan/Instance/Instance.h"

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
		Device(Instance& instance, VkSurfaceKHR surface);

		Device(const Device&) = delete;
		Device(Device&&) = delete;
		void operator=(const Device&) = delete;
		Device& operator=(Device&&) = delete;

		VkDevice* Pointer() { return &Logical; }
		const VkDevice* Pointer() const { return (const VkDevice*)&Logical; }

		operator VkDevice() const { return Logical; }
		operator VkPhysicalDevice() const { return Physical; }

	private:
		Instance& m_Instance;
		VkSurfaceKHR m_Surface;

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