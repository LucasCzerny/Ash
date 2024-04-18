#include "pch.h"
#include "Window.h"

#include "Core/Assert.h"
#include "Core/ErrorCallbacks.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	Window::Window()
		: Width(Config::Get().Width), Height(Config::Get().Height), Extent2D{Width, Height}, Extent3D{Width, Height, 0}
	{
		static Context& context = Context::Get();
        static Config& config = Config::Get();

		glfwSetErrorCallback(GlfwErrorCallback);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		Handle = glfwCreateWindow(config.Width, config.Height, config.Title.c_str(), nullptr, nullptr);

		glfwWindowHint(GLFW_RESIZABLE, config.Resizable);

		VkResult result = glfwCreateWindowSurface(context.Instance, Handle, NULL, &Surface);
		ASSERT(result == VK_SUCCESS, "Failed to create the window surface.");
	}

	Window::~Window()
	{
		static Context& context = Context::Get();

		vkDestroySurfaceKHR(context.Instance, Surface, nullptr);
		glfwDestroyWindow(Handle);
	}

	void Window::Resize(uint32_t width, uint32_t height)
	{
		Width = width;
		Height = height;

		LastResizeTime = (float)glfwGetTime();
	}

	float Window::GetDeltaTime() const
	{
		static float lastTime = 0.0f;

		float time = (float)glfwGetTime();
		float deltaTime = time - lastTime;
		lastTime = time;

		return deltaTime;
	}
}