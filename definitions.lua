outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["vulkan"] = "%{VULKAN_SDK}/Include"

VULKAN_SDK = os.getenv("VULKAN_SDK")
VulkanLibraryDir = "%{VULKAN_SDK}/Lib"
VulkanLibrary = "vulkan-1"