#pragma once

namespace Ash
{
	class Config
	{
	public:
		// App Settings
		std::string Title = "Ash Application";
		uint32_t Major = 0, Minor = 1, Patch = 0;
		uint32_t Width = 1280, Height = 720;
		bool Fullscreen = false;
		bool Resizable = true;

		#ifdef ASH_DEBUG
			bool EnableValidationLayers = true;
		#else
			bool EnableValidationLayers = false;
		#endif

		std::vector<const char*> ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
		std::vector<const char*> InstanceExtensions = { "VK_EXT_debug_utils" };
		std::vector<const char*> DeviceExtensions = { "VK_KHR_swapchain", "VK_EXT_descriptor_indexing" };

		uint32_t MaxFramesInFlight = 2;
		uint32_t MaxNumberOfModels = 1000;
		uint32_t MaxNumberOfMaterials = 10000;
		uint32_t MaxNumberOfLights = 64;

		bool AnisotropicSampling = true;

	public:
		static Config& Get();
	
		VkDebugUtilsMessengerCreateInfoEXT GetDebugMessengerInfo();
	};
}