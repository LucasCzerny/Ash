#pragma once

#include "Vulkan/Context/Context.h"
#include "Config/Config.h"

namespace Ash::Vulkan
{
	class Window
	{
	public:
		GLFWwindow* Handle;
		VkSurfaceKHR Surface;

		uint32_t Width, Height;
		VkExtent2D Extent2D;
		VkExtent3D Extent3D;

		float LastResizeTime = 0.0f;

	public:
		Window(const Config& config);
		~Window();

		// Not copyable or moveable
		Window(const Window&) = delete;
		void operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		void Resize(uint32_t width, uint32_t height);

		glm::vec2 GetSize() const { return glm::vec2{ Width, Height }; }
		VkExtent2D GetExtent2D() const { return VkExtent2D{ Width, Height }; }
		VkExtent3D GetExtent3D() const { return VkExtent3D{ Width, Height, 0 }; }

		operator GLFWwindow*() const { return Handle; }

	private:
		Context& m_Context;
	};
}