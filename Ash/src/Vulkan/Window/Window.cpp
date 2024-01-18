#include "pch.h"
#include "Window.h"

#include "Core/Assert.h"
#include "Core/ErrorCallbacks.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	Window::Window(const Config& config)
		: m_Context(Context::Get()), Width(config.Width), Height(config.Height), Extent2D{ Width, Height }, Extent3D{ Width, Height, 0 }
	{
		glfwSetErrorCallback(GlfwErrorCallback);

		ASSERT(glfwInit(), "Failed to initialize GLFW.");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		Handle = glfwCreateWindow(config.Width, config.Height, config.Title.c_str(), nullptr, nullptr);

		glfwWindowHint(GLFW_RESIZABLE, config.Resizable);

		VkResult result = glfwCreateWindowSurface(m_Context.Instance, Handle, NULL, &Surface);
		ASSERT(result == VK_SUCCESS, "Failed to create the window surface.");
	}

	Window::~Window()
	{
		vkDestroySurfaceKHR(m_Context.Instance, Surface, nullptr);
		glfwDestroyWindow(Handle);
	}

	void Window::Resize(uint32_t width, uint32_t height)
	{
		Width = width;
		Height = height;

		LastResizeTime = glfwGetTime();
	}
}