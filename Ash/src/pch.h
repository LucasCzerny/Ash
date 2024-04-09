#pragma once

// STD

#include <iostream>
#include <cinttypes>
#include <memory>
#include <functional>

#include <string>
#include <sstream>

#include <fstream>
#include <filesystem>

namespace Ash
{
	namespace fs = std::filesystem;
}

#include <array>
#include <vector>
#include <set>
#include <unordered_set>

// ENTT

#include <entt/entt.hpp>

// GLFW

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// GLM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Quaternions are still experimental :o
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

// IMGUI

#include <imgui.h> 
#include <misc/freetype/imgui_freetype.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

// STB IMAGE

#include <stb_image.h>

// TINYGLTF

#include <tiny_gltf.h>

// WHY THE FUCK DOES WINDEF.H DEFINE THESE?!?!?!?

#undef near
#undef far
#undef ERROR
#undef CreateWindow
#undef LoadTexture