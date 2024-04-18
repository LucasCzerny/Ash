#include "pch.h"
#include "Context.h"

#include "Events/EventDispatcher.h"

#include "Core/Assert.h"
#include "Core/ErrorCallbacks.h"

#include "Vulkan/Defaults/Defaults.h"
#include "Vulkan/Device/Device.h"
#include "Vulkan/Window/Window.h"
#include "Vulkan/SwapChain/SwapChain.h"

#include "Events/WindowEvents.h"

namespace Ash::Vulkan
{
	Context Context::s_Instance;

	Context::Context()
	{
		CreateCommandPool();
		CreateCommandBuffers();

		CreateDescriptorPool();

		CreateEventCallbacks();
	}

	Context::~Context()
    {
        glfwTerminate();

        if (Config::Get().EnableValidationLayers)
        {
            auto func = GetExtensionFunction<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT");
            func(Instance, m_DebugMessenger, nullptr);
        }
    }

	void Context::Resize(uint32_t width, uint32_t height)
	{
		Window.Resize(width, height);
		SwapChain.Recreate();
	}

	VkCommandBuffer Context::GetNextCommandBuffer()
	{
		static uint32_t index = 0;

		uint32_t currentIndex = index;
		index = (index + 1) % CommandBuffers.size();

		return CommandBuffers[currentIndex];
	}

    void Context::CreateCommandPool()
    {
        VkCommandPoolCreateInfo poolCreateInfo{};
        poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

        poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolCreateInfo.queueFamilyIndex = Device.GraphicsQueue.Family;

        VkResult result = vkCreateCommandPool(Device, &poolCreateInfo, nullptr, &CommandPool);
		ASSERT(result == VK_SUCCESS, "Failed to create the command pool.");
    }

	void Context::CreateCommandBuffers()
	{
		CommandBuffers.resize(SwapChain.ImageCount);

		VkCommandBufferAllocateInfo allocInfo = Defaults<VkCommandBufferAllocateInfo>();
		allocInfo.commandBufferCount = (uint32_t)CommandBuffers.size();

		VkResult result = vkAllocateCommandBuffers(Device, &allocInfo, CommandBuffers.data());
		ASSERT(result == VK_SUCCESS, "Failed to allocate the command buffers.");
	}

    void Context::CreateDescriptorPool()
    {
		std::array<VkDescriptorPoolSize, 11> poolSizes{ {
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		} };

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;

		poolInfo.maxSets = 1000;
		poolInfo.poolSizeCount = (uint32_t)poolSizes.size();
		poolInfo.pPoolSizes = poolSizes.data();

		VkResult result = vkCreateDescriptorPool(Device, &poolInfo, nullptr, &DescriptorPool);
		ASSERT(result == VK_SUCCESS, "Failed to create the descriptor pool.");
    }

	void Context::CreateEventCallbacks()
	{
		glfwSetWindowSizeCallback(Window, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			EventDispatcher::Dispatch(event);
		});
	}
}
