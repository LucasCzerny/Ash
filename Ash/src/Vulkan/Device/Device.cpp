#include "pch.h"
#include "Device.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	Device::Device(Instance& instance, VkSurfaceKHR surface)
        : m_Instance(instance), m_Surface(surface)
	{
        ChoosePhysicalDevice();
        ChooseLogicalDevice();
        GetQueues();
	}

    void Device::ChoosePhysicalDevice()
    {
        uint32_t physicalDeviceCount;
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, physicalDevices.data());

        Physical = VK_NULL_HANDLE;

        for (const VkPhysicalDevice& device : physicalDevices)
        {
            std::array<uint32_t, 2> queueFamilies = GetQueueFamilies(device);
            SwapChainSupport = QuerySwapChainSupport(device);

            if (queueFamilies[0] < UINT32_MAX && queueFamilies[1] < UINT32_MAX && IsDeviceSuitable(device))
            {
                Physical = device;
                GraphicsQueue.Family = queueFamilies[0];
                PresentQueue.Family = queueFamilies[1];

                break;
            }
        }

        ASSERT(Physical != VK_NULL_HANDLE, "Couldn't find a suitable GPU.");
    }

    std::array<uint32_t, 2> Device::GetQueueFamilies(VkPhysicalDevice device)
    {
        std::array<uint32_t, 2> queueFamilies = { UINT32_MAX, UINT32_MAX };

        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> familyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, familyProperties.data());

        for (int i = 0; i < familyProperties.size(); i++)
        {
            const VkQueueFamilyProperties& family = familyProperties[i];

            bool hasGraphicsFamily = false, hasPresentFamily = false;

            if (family.queueCount <= 0)
            {
                continue;
            }

            if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                queueFamilies[0] = i;
            }

            VkBool32 presentSupport = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);

            if (presentSupport)
            {
                queueFamilies[1] = i;
            }

            if (hasGraphicsFamily && hasPresentFamily)
            {
                break;
            }
        }

        return queueFamilies;
    }

    DeviceSwapChainSupport Device::QuerySwapChainSupport(VkPhysicalDevice device)
    {
        DeviceSwapChainSupport support{};

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &support.Capabilities);

        uint32_t surfaceFormatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &surfaceFormatCount, nullptr);

        if (surfaceFormatCount != 0)
        {
            support.SurfaceFormats.resize(surfaceFormatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &surfaceFormatCount, support.SurfaceFormats.data());
        }

        uint32_t presentModesCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModesCount, nullptr);

        if (presentModesCount != 0)
        {
            support.PresentModes.resize(presentModesCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModesCount, support.PresentModes.data());
        }

        return support;
    }

    bool Device::IsDeviceSuitable(VkPhysicalDevice device)
    {
        static Config& config = Config::Get();

        bool suitable = SwapChainSupport.IsComplete() && SupportsRequiredExtensions(device);
        suitable &= (!config.AnisotropicSampling || SupportsAnisotropicSampling(device));

        return suitable;
    }

    bool Device::SupportsRequiredExtensions(VkPhysicalDevice device)
    {
        static std::vector<const char*>& deviceExtensions = Config::Get().DeviceExtensions;

        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    bool Device::SupportsAnisotropicSampling(VkPhysicalDevice device)
    {
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(device, &features);

        return features.samplerAnisotropy;
    }

    void Device::ChooseLogicalDevice()
    {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        std::set<uint32_t> uniqueQueueFamilies = { GraphicsQueue.Family, PresentQueue.Family };

        for (uint32_t queueFamilyIndex : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo = Defaults<VkDeviceQueueCreateInfo>();
            {
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            }

            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkDeviceCreateInfo deviceInfo = Defaults<VkDeviceCreateInfo>();
        {
			deviceInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
			deviceInfo.pQueueCreateInfos = queueCreateInfos.data();

			VkPhysicalDeviceDescriptorIndexingFeatures indexingFeatures{};
			indexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;

			// indexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
			// indexingFeatures.runtimeDescriptorArray = VK_TRUE;
			// indexingFeatures.descriptorBindingVariableDescriptorCount = VK_TRUE;
			indexingFeatures.descriptorBindingPartiallyBound = VK_TRUE;

			deviceInfo.pNext = &indexingFeatures;
        }

        VkResult result = vkCreateDevice(Physical, &deviceInfo, nullptr, &Logical);
        ASSERT(result == VK_SUCCESS, "Failed to create the logical device.");
    }

    void Device::GetQueues()
    {
        vkGetDeviceQueue(Logical, GraphicsQueue.Family, 0, GraphicsQueue.Pointer());
        vkGetDeviceQueue(Logical, PresentQueue.Family, 0, PresentQueue.Pointer());
    }
}