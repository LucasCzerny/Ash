#pragma once

#include "Config/Config.h"

#include "Vulkan/Device/Device.h"
#include "Vulkan/Window/Window.h"
#include "Vulkan/SwapChain/SwapChain.h"

namespace Ash::Vulkan
{
	class Context
	{
	public:
		VkInstance Instance;
		Vulkan::Window Window;

		Vulkan::Device Device;

		Vulkan::SwapChain SwapChain;

		VkCommandPool CommandPool;
		std::vector<VkCommandBuffer> CommandBuffers;

		VkDescriptorPool DescriptorPool;

	public:
		Context(Config& config);
		~Context();

		static Context& Get();

		void Resize(uint32_t width, uint32_t height);

		VkCommandBuffer GetNextCommandBuffer();

		template <typename T>
		T GetExtensionFunction(const std::string& name);

	private:
		Config& m_Config;

		VkDebugUtilsMessengerEXT m_DebugMessenger;

	private:
		void CreateCommandPool();
		void CreateCommandBuffers();

		void CreateDescriptorPool();

		void CreateEventCallbacks();
	};
}

#include "Context.inl"