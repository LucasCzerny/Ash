Ash_IncludeDir["imgui"] = "../vendor/imgui/imgui/"

project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. Ash_outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. Ash_outputdir .. "/%{prj.name}")
	
	files
	{
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_demo.cpp",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_vulkan.cpp"
	}

	includedirs
	{
		"%{Ash_IncludeDir.vulkan}",
		"imgui",
		"../glfw/glfw/include"
	}
	
	links
	{
		"GLFW"
	}
	
	defines
	{
		"IMGUI_USE_WCHAR32"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"