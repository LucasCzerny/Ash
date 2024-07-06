#include "pch.h"
#include "Instance.h"

#include "Config/Config.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	Instance::Instance()
	{
		static Config& config = Config::Get();
    
        // TODO: when the imposter is sus
		ASSERT(glfwInit(), "Failed to initialize GLFW.");

        // TODO: Move this to the config class ???
        ASSERT(config.EnableValidationLayers <= CheckValidationLayerSupport(), "Validation layers requested, but not available.");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = config.Title.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(config.Major, config.Minor, config.Patch);
        appInfo.pEngineName = "Ash";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags = NULL;

        uint32_t glfwExtensionCount;
        const char** glfwExtensionsArray = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> glfwExtensions(glfwExtensionsArray, glfwExtensionsArray + glfwExtensionCount);
        std::vector<const char*> extensions = config.InstanceExtensions;
        extensions.reserve(extensions.size() + glfwExtensions.size());
        extensions.insert(extensions.end(), glfwExtensions.begin(), glfwExtensions.end());

        createInfo.enabledExtensionCount = (uint32_t)extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        std::vector<const char*> validationLayers = config.ValidationLayers;

        if (config.EnableValidationLayers)
        {
            createInfo.enabledLayerCount = (uint32_t)(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = config.GetDebugMessengerInfo();
            createInfo.pNext = &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &Handle);
        ASSERT(result == VK_SUCCESS, "Failed to create the instance.");
	}

    bool Instance::CheckValidationLayerSupport()
    {
        static Config& config = Config::Get();

        std::vector<const char*> validationLayers = config.ValidationLayers;

        uint32_t propertyCount;
        vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(propertyCount);
        vkEnumerateInstanceLayerProperties(&propertyCount, availableLayers.data());

        for (const char* requestedLayerName : validationLayers)
        {
            bool layerAvailable = false;

            for (const VkLayerProperties& properties : availableLayers)
            {
                if (strcmp(properties.layerName, requestedLayerName) == 0)
                {
                    layerAvailable = true;
                }
            }

            if (!layerAvailable)
            {
                return false;
            }
        }

        return true;
    }
}