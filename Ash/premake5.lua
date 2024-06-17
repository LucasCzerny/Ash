project "Ash"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	targetdir ("../bin/" .. Ash_outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. Ash_outputdir .. "/%{prj.name}")

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

		"%{Ash_IncludeDir.vulkan}",
		"%{Ash_IncludeDir.entt}",
		"%{Ash_IncludeDir.glfw}",
		"%{Ash_IncludeDir.glm}",
		"%{Ash_IncludeDir.imgui}",
		"%{Ash_IncludeDir.stb}",
		"%{Ash_IncludeDir.tinygltf}"
	}
	
	libdirs
	{
		"%{Ash_VulkanLibraryDir}"
	}
	
	links
	{
		"%{Ash_VulkanLibrary}",
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
