require("cmake")

workspace "Ash"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

include "definitions.lua"

group "External Libs"
	include "vendor/entt"
	include "vendor/glfw"
	include "vendor/glm"
	include "vendor/imgui"
	include "vendor/stb"
	include "vendor/tinygltf"
group ""

include "Ash"
