#include "pch.h"
#include "Config.h"

#include "Application/Application.h"

#include "Core/ErrorCallbacks.h"

namespace Ash
{
	Config& Config::Get()
	{
        static Config config;
        return config;
	}

	VkDebugUtilsMessengerCreateInfoEXT Config::GetDebugMessengerInfo()
	{
        static VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{}; debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        // Call the callback for messages of any severity and any type
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;

        debugCreateInfo.pfnUserCallback = VulkanDebugCallback;

        return debugCreateInfo;
	}
}