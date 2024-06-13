Ash_outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

Ash_IncludeDir = {}

Ash_VULKAN_SDK = os.getenv("VULKAN_SDK")
Ash_IncludeDir["vulkan"] = "%{Ash_VULKAN_SDK}/Include"
Ash_VulkanLibraryDir = "%{Ash_VULKAN_SDK}/Lib"
Ash_VulkanLibrary = "vulkan-1"