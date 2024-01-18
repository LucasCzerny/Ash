workspace "Ash"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SpinningCube"

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
include "SpinningCube"