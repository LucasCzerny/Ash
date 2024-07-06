#include "pch.h"
#include "ErrorCallbacks.h"

#include "Log.h"

namespace Ash
{
	void GlfwErrorCallback(int code, const char* message)
	{
		Log::Error("GLFW ERROR\nCode:", code, " | Message: ", message);
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if (messageSeverity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			return VK_FALSE;
		}

		Log::Error("VULKAN ERROR\n", pCallbackData->pMessage);
		return VK_TRUE;
	}
}