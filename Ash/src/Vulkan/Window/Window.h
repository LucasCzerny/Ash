#pragma once

#include "Config/Config.h"

#include "Vulkan/Instance/Instance.h"

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
		Window(Instance& instance);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		void operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		// TODO: group setter and getter
		void Resize(uint32_t width, uint32_t height);
		glm::vec2 GetSize() const { return glm::vec2{ Width, Height }; }

		bool IsOpen() const { return !glfwWindowShouldClose(Handle); }
		void PollEvents() const { glfwPollEvents(); }

		float GetDeltaTime() const;

		operator GLFWwindow*() const { return Handle; }

	private:
		Instance& m_Instance;
	};
}