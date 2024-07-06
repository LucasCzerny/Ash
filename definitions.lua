outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

VULKAN_SDK = os.getenv("VULKAN_SDK")
IncludeDir["vulkan"] = "%{Ash_VULKAN_SDK}/Include"
VulkanLibraryDir = "%{Ash_VULKAN_SDK}/Lib"
VulkanLibrary = "vulkan-1"
