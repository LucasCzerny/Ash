project "Ash"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"
	
	externalwarnings "Off"

	files 
	{
		"src/**.h", "src/**.cpp", "src/**.inl"
	}
	
	includedirs
	{
		"src",

		"%{IncludeDir.vulkan}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.tinygltf}"
	}
	
	libdirs
	{
		"%{VulkanLibraryDir}"
	}
	
	links
	{
		"%{VulkanLibrary}",
		"GLFW",
		"ImGui"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines { "ASH_PLATFORM_WINDOWS" }
		
	filter "system:linux"
		systemversion "latest"
		defines { "ASH_PLATFORM_LINUX" }

	filter "configurations:Debug"
		defines { "ASH_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "ASH_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "ASH_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"
