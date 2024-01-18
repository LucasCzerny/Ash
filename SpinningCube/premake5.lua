project "SpinningCube"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	externalwarnings "Off"

	files 
	{
		"src/**.h", "src/**.cpp", "src/**.inl"
	}
	
	includedirs
	{
		"src",
		"../Ash/src",

		"%{IncludeDir.vulkan}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.tinygltf}"
	}
	
	links
	{
		"Ash"
	}
	
	filter "system:windows"
		systemversion "latest"
	  
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
		symbols "Off"